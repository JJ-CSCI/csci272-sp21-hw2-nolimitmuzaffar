//------------------------------
//  DO NOT MODIFY NEXT LINE
//------------------------------
#include "catch.hpp"
//------------------------------

// Implement the class methods
class Rot13 {
    const int rotation{13};
    std::string text;
     int dec_conversion;//value of character in decimal according to ascii table. to be used for when encoding a valid input

public:
    Rot13(std::string msg = ""){
      // access each character
      for(unsigned int i = 0; i<msg.length(); i=i+1) {//unsigned is important here because we are trying to nonpositive numbers
         char c = static_cast<int>(msg[i]);
        if((c>=97 && c<= 122) || (c==32)){//check if the character is a lowercase based on decimal value from ascii table
          text = text + msg[i]; //adding to text
          
        }else{
          text.erase();//if not we must clear it
          break;//to terminate the loop if the user enters invalid input
        }
      }
    }
    

//if there's nothing in the string text, return true
bool operator!(){ return text.length() == 0;}

//now we encode 
    void operator>>(std::string& mod){//mod is the parameter, a string that will be modified in this method
      for(unsigned int i =0; i < text.length(); i=i+1){
     dec_conversion = static_cast<int>(text[i]);//getting the int value of each charcter in string text
     if(dec_conversion ==32){//check for space in the string
        mod = mod + static_cast<char>(dec_conversion);
       continue;//to break one itteration in the loop
     }
     dec_conversion = dec_conversion + rotation;//rotation is used to fast forward 13 letters in the alphabet

      if (dec_conversion > 122){ //note that decimal number 122 is letter z
        dec_conversion= dec_conversion-122;
        dec_conversion = dec_conversion+96;
       }
      mod = mod + static_cast<char>(dec_conversion);//adding to the string mod
     
      }
      }
//c >='A' && c <= 'Z'


    friend void operator<<(std::string&, Rot13&);
};

void operator<<(std::string& original_msg, Rot13& encrypted_msg){
  int dec_conversion2;//will use here for deciphering
      for (unsigned int i=0; i<encrypted_msg.text.length(); i=i+1){//has to be unsigned so we wouldn't take neg numbers
        dec_conversion2 = static_cast<int>(encrypted_msg.text[i]);//getting ascii value of character at position i and setting to dec_conversion
        if (dec_conversion2==32){//to see if there's a space in the string
          original_msg = original_msg + static_cast<char>(dec_conversion2);
          continue;//to break one itteration in this loop
        }
        dec_conversion2 = dec_conversion2 - encrypted_msg.rotation;//we are reversing Rot13 key encryption since we are trying to go back 13 characters to decode
        if (dec_conversion2 < 97){
          dec_conversion2=97-dec_conversion2;
          dec_conversion2=123-dec_conversion2;
        }

    original_msg= original_msg+ static_cast<char>(dec_conversion2);
        //gets added to the string original_msg and the loop continues until the condition is met

      }
    }

//};


//------------------------------
//   DO NOT MODIFY TEST CASES
//------------------------------
TEST_CASE( "Assignment" ) {
    SECTION( "v1" ) {
        Rot13 cipher;
        REQUIRE( !cipher );
    }
    SECTION( "v2" ) {
        Rot13 cipher{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        REQUIRE( !cipher );
    }
    SECTION( "v3" ) {
        Rot13 cipher{"slkgjskjg  akjf Adkfjd fsdfj"};
        REQUIRE( !cipher );
    }
    SECTION( "v4" ) {
        Rot13 cipher{"abcdefghijkl mnopqrst uvwxyz"};
        REQUIRE( !!cipher );
    }
    SECTION( "e1" ) {
        Rot13 cipher{"abcdefghijkl mnopqrst uvwxyz"};
        REQUIRE( !!cipher );
        std::string secret;
        cipher >> secret;
        REQUIRE( secret == "nopqrstuvwxy zabcdefg hijklm" );
    }
    SECTION( "e2" ) {
        Rot13 cipher{"nopqrstuvwxy zabcdefg hijklm"};
        REQUIRE( !!cipher );
        std::string msg;
        msg << cipher;
        REQUIRE( msg == "abcdefghijkl mnopqrst uvwxyz" );
    }
}
//------------------------------
