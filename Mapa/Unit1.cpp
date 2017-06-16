//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//variavel axuiliar para traçar uma reta
int aux_x=0;
int aux_y=0;

//variaveis auxiliar para lipar uma reta
int ap_x1=0;
int ap_y1=0;
int ap_x2=0;
int ap_y2=0;

Graphics::TBitmap *Bmp = new Graphics::TBitmap;
 // pinta pixel
void Pintap (double x, double y,double r,double g,double b){
Bmp = Form1->Image1->Picture->Bitmap;
Bmp->Canvas->Pixels[x][y]= RGB(r,g,b);
}
//desenha arco
void dArc(int xc, int xy, int raio, int ti, int tf) {
         Bmp = Form1->Image1->Picture->Bitmap;
        Bmp->Canvas->MoveTo( xc,xy);
        for ( int teta= ti; teta<=tf; teta++) {
               int x = xc + raio * cos(teta) ;
               int y = xy + raio * sin(teta);
                Pintap (x,y,255,0,0);
        }
 }

String aux_estado="";

//liberar capitais
void libera()
{
                Form1->Image2->Enabled = true;
                Form1->Image3->Enabled = true;
                Form1->Image4->Enabled = true;
                Form1->Image5->Enabled = true;
                Form1->Image6->Enabled = true;
                Form1->Image7->Enabled = true;
}
//escrever
void frase(String frase)
{
        Bmp->Canvas->Font->Color = RGB(0,0,0);
        Bmp->Canvas->Font->Size = 8;
        Bmp->Canvas->Font->Name = "Trebuchet MS";
        Bmp->Canvas->Font->Style = TFontStyles() << fsBold << fsUnderline;
        Bmp->Canvas->TextOutA(0,350,frase);
}
//Tracejar distancia
void distancia(int x1,int y1,String estado)
{

if(aux_x != 0 && aux_y != 0)
{

        Bmp = Form1->Image1->Picture->Bitmap;
        Bmp->Canvas->Pen->Color = RGB(0,0,0);
        Bmp->Canvas->Pen->Style = PS_DOT;
        Bmp->Canvas->MoveTo(aux_x,aux_y);
        Bmp->Canvas->LineTo(x1,y1);

        aux_x = 0;
        aux_y = 0;

        libera();

        if((aux_estado=="sp" && estado == "rj") || (estado=="sp" && aux_estado == "rj")){
                frase("São Paulo ao Rio de Janeiro distância  - 450 Km");
        }else{
                if((aux_estado=="sp" && estado == "mg") || (estado=="sp" && aux_estado == "mg")){
                      frase("São Paulo a Minas Gerais distância  - 590 Km");
                }else{
                        if((aux_estado=="sp" && estado == "ba") || (estado=="sp" && aux_estado == "ba")){
                                frase("São Paulo até  Salvador (Bahia) - 1965 Km");
                        }else{
                                if((aux_estado=="rj" && estado == "go") || (estado=="rj" && aux_estado == "go")){
                                        frase("Rio de Janeiro a Brasília - 1268 Km");
                                }else{
                                        if((aux_estado=="rj" && estado == "mg") || (estado=="rj" && aux_estado == "mg")){
                                                frase("Rio de Janeiro a Belo Horizonte - 485 Km");
                                        }else{
                                                if((aux_estado=="pe" && estado == "sp") || (estado=="pe" && aux_estado == "sp")){
                                                        frase("Recife(Pernambuco) a São Paulo - 2800Km");
                                                }
                                        }
                                }
                        }
                }
        }
        aux_estado = "";
        Form1->mp2->Picture->LoadFromFile("c:/proj cg/img/"+estado+".bmp");
}else{
        aux_x = x1;
        aux_y = y1;
        aux_estado = estado;
        Form1->mp1->Picture->LoadFromFile("c:/proj cg/img/"+estado+".bmp");
        Form1->mp2->Picture->LoadFromFile("c:/proj cg/img/branco.bmp");
}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
//Bahia
dArc(Image2->Left,Image2->Top,20,0,360);
distancia(Image2->Left,Image2->Top,"ba");
Image2->Enabled = false;
Image3->Enabled = false;
Image4->Enabled = false;
Image5->Enabled = false;
Image6->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3Click(TObject *Sender)
{
//Recife
dArc(Image3->Left,Image3->Top,20,0,360);
libera();
Image2->Enabled = false;
Image3->Enabled = false;
Image4->Enabled = false;
Image5->Enabled = false;
Image6->Enabled = false;
distancia(Image3->Left,Image3->Top,"pe");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image6Click(TObject *Sender)
{
//Basilia
distancia(Image6->Left,Image6->Top,"go");
Image2->Enabled = false;
Image3->Enabled = false;
Image5->Enabled = false;
Image6->Enabled = false;
Image7->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image4Click(TObject *Sender)
{
//Rio de Janeiro
dArc(Image4->Left,Image4->Top,20,0,360);
libera();
Image4->Enabled = false;
Image3->Enabled = false;
distancia(Image4->Left,Image4->Top,"rj");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image5Click(TObject *Sender)
{
//Belo Horizonte
distancia(Image5->Left,Image5->Top,"mg");
Image2->Enabled = false;
Image3->Enabled = false;
Image5->Enabled = false;
Image6->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image7Click(TObject *Sender)
{
//São Paulo
libera();
Image7->Enabled = false;
Image6->Enabled = false;
distancia(Image7->Left,Image7->Top,"sp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Image1->Picture->SaveToFile("C:/proj cg/customizado.bmp");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
aux_x = 0;
aux_y = 0;
Bmp->LoadFromFile("C:/proj cg/img/mapa.bmp");
mp1->Picture->LoadFromFile("C:/proj cg/img/branco.bmp");
mp2->Picture->LoadFromFile("C:/proj cg/img/branco.bmp");
libera();
}
//---------------------------------------------------------------------------








