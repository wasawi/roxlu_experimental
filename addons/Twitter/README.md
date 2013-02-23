Twitter
--------
Standalone minimal twitter library for C++ using the fast libuv library and openssl. 
  This library only has two dependencies for which static libraries are included.
  - OpenSSL 1.01
  - libuv, hash: 149b16f1232d8fdcf5436534d6ade6f9877e1b8f 
  - To compile add an include path to: `addons/Twitter/include` and ...
  - .. make sure that you add the sources of the Twitter addon to your project. These are 
  
    - `Twitter/src/twitter/*.cpp`
    - `Twitter/extern/format/*.*`
  

  
    
How to use this library
========================

Step 1: Create an Twitter application
--------------------------------------
- Go to http://dev.twitter.com/ and follow the steps to create a new application. If you follow the example applications
from `roxlu/apps/examples/twitter_get_tokens` then you need to change the values passed into `tw.setConsumer()` and `tw.setConsumerSecrect`
with the values of the application you created on http://dev.twitter.com

Step 2: Create a SSL private key
---------------------------------

- First you need to create a private key for SSL, follow these steps (self signed certificate): Create a key for the Certificate Authority certificate (CA-certificate)
   
`$ openssl genrsa 2048 > ca-key.pem`
      

- Create a certificate with this key, you can leave all fields empty (just press enter) (nodes = no password):
   
`$ openssl req -new -x509 -nodes -days 36000 -key ca-key.pem -out ca-cert.pem`
    

- Create client certificate, remove passphrase and sign it with the CA certificate
    
`$ openssl req -newkey rsa:2048 -days 36000 -nodes -keyout client-key.pem -out client-req.pem`

 `$ openssl rsa -in client-key.pem -out client-key.pem`
    
 `$ openssl x509 -req -in client-req.pem -days 36000 -CA ca-cert.pem -CAkey ca-key.pem -set_serial 01 -out client-cert.pem`
    

**You now have the following files**
  - client-cert.pem = public key
  - client-key.pem = private key

**Use the `client-key.pem` for your twitter applications**
      
Step 3: Get a access token:
----------------------------
- See the example application in `roxlu/apps/examples/twitter_get_tokens/`.
  This is a plain simple c++ application that you can compile directly using 
  gcc/g++ or XCode. You should run this application from the command line. It 
  will ask you to open an url from twitter. When you open this link you need to 
  grant the application so it can use your account to connect to the twitter 
  servers.

- After you've granted your account + application, you will see a PIN that you 
  need to enter on the command line. Then press enter.

- The twitter_get_tokens application will then exchange the PIN for an 
  authorization token and secret. Keep these codes private, but add them 
  to your application. See twitter_streaming_example where we use these 
  tokens. See the main.cpp file comments about creating a twitter_tokens.h 
  file, with this contents:

<pre>
tw.setToken("TOKEN");
tw.setTokenSecret("SOME_TOKEN_SECRET");
</pre>


Step 4: Use your access tokens to make API calls
-------------------------------------------------
- Make sure you've created a ssl key and use this in you application 
- Once you've got an access token you can start using the library and 
  make API calls. You can see two example API calls in the Twitter class, see
  apiStatusesUpdate() and apiStatusesFilter()
- This library does not parse the API responses

