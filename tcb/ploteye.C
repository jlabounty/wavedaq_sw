{
  TNtuple *my = new TNtuple("my","my","dly:bit:sl0:sl1:sl2:sl3:sl4:sl5:sl6:sl7:sl8:sl9:sl10:sl11:sl12:sl13:sl4:sl15");
  my->ReadFile("tres.dat");
  my->SetMarkerStyle(20);
  my->Draw("sl0:dly","bit==3");
}
