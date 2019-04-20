void sendStatus(String s)
{
  String stat = " Status: " + s;
  nexSerial.print("t1.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.print(stat);  // This is the value you want to send to that object and atribute mentioned before.
  nexSerial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  nexSerial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  nexSerial.write(0xff);
  nexSerial.write(0xff);
}
