

 int SoundPin= 11;

 //int i=1;int j = 1;
	int i, j, Dlit, Freq;
	  int Niz, Verh, Osnova, Shag; // переменные для работы со звуком
	  int Razmah, DlitZvukPauza, ChisloZvukov;
void setup() {
	// Речь ведроида
	              for (i=1;i<11; i++)
	              {
	                  Osnova = 100 + random(3000);
	                  DlitZvukPauza = 20;
	                  ChisloZvukov = 3 + random(10);
	                  for (j = 1; j<=ChisloZvukov; j++)
	                  {
	                      Freq = Osnova  + random(Osnova*0.3);
	                      Dlit = DlitZvukPauza * 0.5 +random(DlitZvukPauza*0.5);
	                      tone(SoundPin,Freq, Dlit);
	                      delay(Dlit);
	                      Dlit = DlitZvukPauza - Dlit;
	                      delay(Dlit);
	                    }
	              }
}


void loop() {


}
