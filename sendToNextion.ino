void  sendToNextion(void) {
  String daynow = String(dayStr(weekday())) + " " + day() + daySuffix(day()) + " " + monthStr(month()) + " " + year();
  sprintf(outtime, "%02d:%02d:%02d", hour(), minute(), second());

  //time
  nexSerial.print("time.txt=");
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(outtime);
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  //day date
  nexSerial.print("daydate.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(daynow);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  //place
  nexSerial.print("t0.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(lplace);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);


  //humidity
  nexSerial.print("hum.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(lhum);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.print("%RH");
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  // temperature
  nexSerial.print("temp.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(ltemp);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.print("C");
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  //pressure
  nexSerial.print("pres.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(lpres);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.println("mBar");
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  //icon
  nexSerial.print("icon.pic=");
  nexSerial.print(iconn);
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);


  //desc
  nexSerial.print("desc.txt=");
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(descString);
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);

}

String daySuffix (uint8_t day)
{
  String ordinal_suffix;
  switch (day) {
    case 1:
    case 21:
    case 31: ordinal_suffix = "st"; break;
    case 2:
    case 22: ordinal_suffix = "nd"; break;
    case 3:
    case 23: ordinal_suffix = "rd"; break;
    default: ordinal_suffix = "th";
  };
  return ordinal_suffix;
}
