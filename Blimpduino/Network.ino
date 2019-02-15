// BROBOT EVO 2 by JJROBOTS
// SELF BALANCE ARDUINO ROBOT WITH STEPPER MOTORS
// License: GPL v2
// Network functions (ESP module)



String sParams[9];

void MsgRead()
{
  String serialdata="";
  uint8_t i;
  // New bytes available to process?
  if (Serial1.available() > 0) {
    serialdata=Serial1.readStringUntil('\n');

    if(serialdata[0] == '#')
    {
      SerialUSB.print("RECV: ");
      SerialUSB.println(serialdata);  

      newMessage = 1;
      int iCount, i;
      iCount = StringSplit(serialdata,' ',sParams,7);

    // print the extracted paramters
    for(i=1;i<iCount;i++) {
       if(i==1) { iCH1 = sParams[i].toInt(); }
       if(i==2) { iCH2 = sParams[i].toInt(); }
       if(i==3) { iCH3 = sParams[i].toInt(); }
       if(i==4) { iCH4 = sParams[i].toInt(); }
       if(i==5) { iCH5 = sParams[i].toInt(); }
       if(i==6) { iCH6 = sParams[i].toInt(); }
       if(i==7) { iCH7 = sParams[i].toInt(); }
       if(i==8) { iCH8 = sParams[i].toInt(); }      
   
     } 
    }
 }
}

int StringSplit(String sInput, char cDelim, String sParams[], int iMaxParams)
{
    int iParamCount = 0;
    int iPosDelim, iPosStart = 0;

    do {
      
        // Searching the delimiter using indexOf()
        iPosDelim = sInput.indexOf(cDelim,iPosStart);
        
        if (iPosDelim >= (iPosStart+1)) {
          
            // Adding a new parameter using substring() 
            sParams[iParamCount] = sInput.substring(iPosStart,iPosDelim);
            iParamCount++;
            // Checking the number of parameters
            if (iParamCount >= iMaxParams) {
                return (iParamCount);
            }
            iPosStart = iPosDelim + 1;
        }
    } while (iPosDelim >= 0);
    if (iParamCount < iMaxParams) {
        // Adding the last parameter as the end of the line
        sParams[iParamCount] = sInput.substring(iPosStart);
        iParamCount++;
    }
    return (iParamCount);
}


