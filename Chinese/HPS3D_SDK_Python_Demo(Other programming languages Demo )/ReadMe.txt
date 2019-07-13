************************************************** *****************************
Readme HPS3D_SDK Python Demo

Hypersen Technologies Copyright © 2019 Version 11.7.19
************************************************** *****************************

A. Folder structure

- HPS3D_Server: As a server, processing the instructions sent by the client to call the interface in the API

- HPS3D_Python_Client:Send relevant instructions to the server to indirectly call the interface in the API according to the specified protocol.


B. HPS3D_Server:

-api.h: This includes all control interfaces of the HPS3D160

-lihps3dxx.so: This is a 32 or 64 bit .so file compiled by generic gcc, depending on your system choice.

-makefile:This is the parameter required for HPS3D_Server compilation, where hps3dxx is set according to the .so file.

-server.c:This is the C language call xxx.so file as a server for other languages to call xxx.so.According to your own defined command control protocol, you can refer to this file to make corresponding modifications. 
 1. Creat_socket: Create a server socket and listen
 2. wait_client: Waiting for client connection
 3. hanld_client: Handling instructions sent by the client
 4. Close the server.

Note: Measurement data is processed in User_Func


!!! IMPORTANT: The client and server communication protocol is "Command,parameter 1,parameter 2 , ..."


-client.py: Send relevant instructions to the server, the specific control sensor operation is performed on the server's HPS3D_CommandProcessFunc(...)


Note:Other programming languages can also use this method to use the SDK.























