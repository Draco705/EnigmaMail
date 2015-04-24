PROGS = encrypt decrypt rotorgenerate

all:	${PROGS}

encrypt:
	gcc -g -Wall enigma.c -o encrypt

decrypt:
	gcc -g -Wall enigma2.c -o decrypt

rotorgenerate:
	gcc -g -Wall rotorgenerate.c -o rotorgenerate

clean:
	rm encrypt
	rm decrypt
	rm rotorgenerate
	rm rotors.txt
	rm adjust.txt
	rm encryptedMessage.txt

hellstorm:
	rm *