void postIt(double loadPower) {

  String qm = "\""; //separator of quotation marks ("")

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;
    String aspas = "\"";
    String serial = "sensorCorrente2";
    String data_hora = updateHoraAtual();
    String postMessage;
  
    http.begin("https://api.saiot.ect.ufrn.br/v1/history/tomada" , key);
    http.addHeader("Content-Type", "application/json");
    postMessage = "[{\"dados\": [{ " + aspas + "serial" + aspas + ": " + aspas + serial + aspas + ", ";
    postMessage += aspas + "data_hora" + aspas + ": " + aspas + data_hora + aspas + ", ";
    postMessage += aspas + "pulso" + aspas + ": " + loadPower + "}], \"data_hora\": " + aspas + data_hora + aspas + " }]";
    
    int httpCode = http.POST(postMessage);
    Serial.println(httpCode);
    
   /* while(httpCode != 200){
      Serial.println("Atualizando fingerPrint");
      updateFingerPrint();
      httpCode = http.POST(postMessage);
      delay(3000);
    }

    http.end();
  } else {
    Serial.print("Error in Wifi connection");
  } */
    
  //While?   
  switch (httpCode) {
    case 200:
      Serial.println ("Conexão OK");
    break;
      
    case 400:
    Serial.println ("Requisição Inválida");
    updateFingerPrint();
    httpCode = http.POST(postMessage);
    delay(3000);
    break;
      
    case 401:
    Serial.println ("Requisição não autorizada");
    updateFingerPrint();
    httpCode = http.POST(postMessage);
    delay(3000);
    break;
   
    case 403:
    Serial.println ("Proibido");
    updateFingerPrint();
    httpCode = http.POST(postMessage);
    delay(3000);
    break;  
    
    case 404:
    Serial.println ("Não encontrado");
    updateFingerPrint();
    httpCode = http.POST(postMessage);
    delay(3000);
    break;
      
    case 500:
    Serial.println ("Erro Interno no Servidor");
    updateFingerPrint();
    httpCode = http.POST(postMessage);
    delay(3000);
    break;
      
    defautl:
      Serial.println ("Nenhum Código de Resposta Encontrado");
  }
  stopGettingData = false; //resetting to begin a new sampling loop
}

void updateFingerPrint(){
  String currentFp; //store the string of the current date requested
  HTTPClient checkFp;
  checkFp.begin("http://auth.saiot.ect.ufrn.br");
  int httpCode = checkFp.GET(); //return the http code anserw
  currentFp = checkFp.getString();
  if(key != currentFp){
    key = currentFp;
  }
}

String getFingerPrint(){
  String currentFp; //store the string of the current date requested
  HTTPClient getFp;
  getFp.begin("http://auth.saiot.ect.ufrn.br");
  do{
    int httpCode = getFp.GET(); //return the http code anserw
    if(httpCode == 200){
      gotFp = true;
      return getFp.getString();
    } else {
      delay(2000);
    }
  }while(!gotFp); //??????? perguntar a Iran
}
