What is ransomware?

Ransomware is a type of malicious software (malware) that threatens to publish or blocks access to data or a computer system, 
usually by encrypting it, until the victim pays a ransom fee to the attacker. In many cases, the ransom demand comes with a deadline. 
If the victim doesn’t pay in time, the data is gone forever or the ransom increases.


Project Summary

This project was developed for the Computer Security course at my academic degree. 
Basically, it will encrypt your files in background using XTEA, an encryption algorithm, using RSA-4096 to secure the exchange with the server, 
optionally using the Tor SOCKS5 Proxy.
The project will be composed by three parts, the server, the malware and the unlocker.

The server will store the victim's identification key along with the encryption key used by the malware.
The malware will encrypt with a RSA-4096 (RSA-OAEP-4096 + SHA256) public key any payload before send then to the server. 
This approach with the optional Tor Proxy and a .onion domain allow you to hide almost completely your server.


TODO

[ ] Run in Background (or not)
[ ] Change encryption cypher to the AES-256-CTR(Counter Mode) with random IV for each file.
[ ] Multithreading
[ ] RSA-4096 to secure the client/server communication
[ ] Include an Unlocker
[ ] Add an optional TOR Proxy support
[ ] Use an AES CTR Cypher with stream encryption to avoid load an entire file into memory.
[ ] Docker image for compilation.
[ ] Daemon
[ ] Dropper
