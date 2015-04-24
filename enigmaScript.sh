#!/bin/bash

# Colton Rudd (coltonr@g.clemson.edu)
# Jeff Grabowski (jgrabow@g.clemson.edu)
# CPSC 424 - Spring 2015
# 22 April 2015
# Project - enigmaScript.sh

# For proper functioning, the following tools need to be installed:
# 	Pandoc - allows for file conversion (here used to convert .txt to .pdf)
#		   - must also get LaTeX!
#	Mutt   - enhanced version of mail command (here used to send attachments through email)
# Install these tools using the following commands:
#	Pandoc :: sudo apt-get install pandoc
#	Mutt   :: sudo apt-get install mutt
#	LaTeX  :: sudo apt-get install texlive


usage () {
	echo "Usage: ./enigmaScript.sh [mode] [arguments]"
	echo "Mode 1: Send & Encrypt"
	echo "./enigmaScript.sh 1 inputFileName recipientAddress senderAddress"
	echo "Mode 2: Encrypt"
	echo "./enigmaScript.sh 2 inputFileName"
	echo "Mode 3: Decrypt"
	echo "./enigmaScript.sh 3 inputFileName"
}

INTEGER_REGEXP='^[1-9][0-9]*$'
MODE_REGEXP='^(1|2|3)$'

mode="$1"
inputFileName="$2"
recipientAddress="$3"
senderAddress="$4"
rotorFile="rotors.txt"
adjustFile="adjust.txt"

# Make sure mode is a positive integer
if ! [[ "$mode" =~ $INTEGER_REGEXP ]] ; then
	echo "[ERROR] mode must be a positive integer"
	usage
	exit -1
fi

# Make sure mode is 1, 2, or 3
if ! [[ "$mode" =~ $MODE_REGEXP ]] ; then
	echo "[ERROR] mode must be 1, 2, or 3"
	usage
	exit -1
fi

# Change permissions on programs so that they can run:
# 	- encrypt
#	- decrypt
#	- Makefile
#	- rotorgenerate

case "$mode" in
	1)
		# Mode 1: Send & Encrypt
		# 	a) Take in text file (plaintext), name for encrypted message, recipient address, and sender address
		# 	b) Encrypt plaintext file > encryptedMessageName.txt (make call to encrypt program)
		# 	c) Send encryptedMessageName.txt and rotors.txt to recipient address
		# 	d) Delete encryptedmsg.txt and rotors.txt

		# If rotors.txt does not exist, generate it
		if [ ! -f "$rotorFile" ] ; then
			chmod 755 rotorgenerate
			./rotorgenerate
		fi

		# Make sure this is being done if rotors.txt is present
		if [ -f "$rotorFile" ]
		then
			# Call the encrypt program to encrypt the message
			chmod 755 encrypt
			./encrypt "$inputFileName"
			# Compress the files to prep for sending
			tar -czvf encrypted.tar.gz "$rotorFile" "$adjustFile" encryptedMessage.txt
			# Set the sending email address
			export EMAIL="$senderAddress"
			# Mail the attachment to the recipient
			mutt -s "Encrypted Message" -a encrypted.tar.gz -- "$recipientAddress"
			# Delete the files after sending for security
			rm -f "$rotorFile" "$adjustFile" encryptedMessage.txt
			echo "Message encrypted and sent."
		else
			echo "[ERROR] rotors.txt is needed!"
		fi
		;;
	2)
		# Mode 2: Encrypt
		# 	a) Take in text file (plaintext), encrypted message name
		# 	b) Make call to encrypt program to encrypt it
		# 	c) Output encryptedMessageName.txt (name is hardcoded in the encrypt program)

		# If rotors.txt does not exist, generate it
		if [ ! -f "$rotorFile" ] ; then
			chmod 755 rotorgenerate
			./rotorgenerate
		fi

		# Make sure this is being done if rotors.txt is present
		if [ -f "$rotorFile" ]
		then
			# Make call to encrypt program and encrypt the message
			chmod 755 encrypt
			./encrypt "$inputFileName"
			echo "Message encrypted"
		else
			echo "[ERROR] rotors.txt is needed!"
		fi
		;;
	3)
		# Mode 3: Decrypt
		# 	a) Take in encrypted message name
		# 	b) Check current directory for rotors.txt and adjust.txt
		#		 i) If not present - throw error and terminate
		#		ii) If present - proceed with decrypting
		# 	c) Make call to decrypt.out to decrypt the message
		# 	d) Convert decrypt.txt to PDF file
		# 	e) Delete rotors.txt, adjust.txt, and decrypt.txt

		# If rotors.txt or adjust.txt are NOT present, quit!
		if [ ! -f "$rotorFile" ] || [ ! -f "$adjustFile" ] ; then
			echo "[ERROR] rotors.txt and adjust.txt not present, cannot decrypt! Terminating."
			exit -l
		fi

		# If rotors.txt and adjust.txt ARE present, proceed with decrypting
		if [ -f "$rotorFile" ] && [ -f "$adjustFile" ]
		then
			# Make call to decrypt program to decrypt the message
			chmod 755 decrypt
			./decrypt "$inputFileName"
			# Use pandoc to convert the text file to a PDF
			pandoc decrypt.txt -o decrypt.pdf
			# Delete the rotors.txt, adjust.txt, and decrypt.txt files
			rm -f "$rotorFile" "$adjustFile" decrypt.txt
			echo "Message decrypted.  View PDF for message."
		fi
		;;
esac
