int parse_json(String r)
{
  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  //DynamicJsonBuffer jsonBuffer(capacity);
  DynamicJsonDocument jdoc(capacity); // V6 edit

  // Parse JSON object
  //JsonObject& root = jsonBuffer.parseObject(r);
  DeserializationError d_error = deserializeJson(jdoc, r); // V6 edit

  if (d_error) {
    DPRINTLN(F("Parsing failed!"));
    return 0;
  }
  else {
    ltemp = jdoc["main"]["temp"];
    lhum = jdoc["main"]["humidity"];
    lpres = jdoc["main"]["pressure"];
    String lcity = jdoc["name"];
    String lctry = jdoc["sys"]["country"];
    String weather = jdoc["weather"][0]["main"];
    String desc = jdoc["weather"][0]["description"];
    String icon = jdoc["weather"][0]["icon"];
    DPRINT(lcity); DPRINT(", "); DPRINTLN(lctry);
    lplace = String(lcity) + ", " + String(lctry);
    String daynight = String(icon[2]);
    DPRINT("daynight = "); DPRINTLN(daynight);
    int iconId = (icon[0] - 0x30) * 10 + (icon[1] - 0x30);
    DPRINT("Icon ID = "); DPRINTLN(iconId);

      switch (iconId)
      {
        case 1:
        case 2:
        case 3:
        case 4:
          iconn = iconId - 1;
          break;
        case 9:
        case 10:
        case 11:
          iconn = iconId - 5;
          break;
        case 13:
          iconn = iconId - 6;
          break;
        case 50:
          iconn = 8;
          break;
        default:
          break;
      }
      if (daynight == "n")
      {
         iconn+=9;
      }

    DPRINT("iconn = "); DPRINTLN(iconn);

    descString = weather + ", "+desc;
    DPRINT("Temperature = "); DPRINTLN(ltemp);
    DPRINT("Humidity = "); DPRINTLN(lhum);
    DPRINT("Pressure = "); DPRINTLN(lpres);
    DPRINT("Weather = "); DPRINTLN(weather);
    DPRINT("Description = "); DPRINTLN(desc);
    DPRINT("Icon = "); DPRINTLN(icon);
  }
}
