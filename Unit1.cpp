//---------------------------------------------------------------------------
// Simple QR Code generator
// Author: Lonchakov Aleksey, Russia, Novosibirsk, june 2019
// Not any limitation on use code from Unit1
// The nayaki library is distributed under the MIT license.
// IDE: C++ Builder 10.3 Community Edition
// sorry for my english :)
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "Unit1.h"

using namespace qrcodegen;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimpleQRCode *FormSimpleQRCode;
//---------------------------------------------------------------------------
__fastcall TFormSimpleQRCode::TFormSimpleQRCode(TComponent* Owner)
  : TForm(Owner)
{
  qr = NULL;  // keep here generated QR Code
  width_pos = 0;  // position in status bar for insert image width
  lang = PRIMARYLANGID(GetUserDefaultLangID()); // language for translate
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::FormDestroy(TObject *Sender)
{
  delete qr;
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::FormCreate(TObject *Sender)
{
  switch(lang)
  {
    case LANG_RUSSIAN: str_type_text = L"Введите текст"; break;
    default:           str_type_text = L"Type text";
  }
  StatusBar1->SimpleText = str_type_text;

  // get text from clipboard on startup
  Memo1->Text = Clipboard()->AsText;
  Memo1->SelStart = Memo1->Text.Length();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  // exit by pressing Escape key
  if(Key==VK_ESCAPE)
    Close();

  // help by pressing F1 key
  if(Key==VK_F1)
  {
    UnicodeString msg;
    switch(lang)
    {
      case LANG_RUSSIAN: msg = L"При запуске кодируется текст из буфера обмена.\n"
                               L"Нажатие л.к. мыши по QR-коду - автомасштаб.\n"
                               L"Нажатие п.к. мыши по QR-коду - контекстное меню.\n"
                               L"Esc - выход из программы.\n\n"
                               L"Программа не требует установки, и работает оффлайн.\n\n"
                               L"В проекте использована библиотека Nayuki\n"
                               L"https://github.com/nayuki/QR-Code-generator\n\n"
                               L"Лицензия: MIT License\n\n"
                               L"Автор: Лончаков Алексей, LonchakovAV@yandex.ru\n"
                               L"Июнь 2019";
                               break;

      default: msg = L"Encoding text from clipboard on startup.\n"
                     L"Pressing the left mouse button on the QR code - auto scale.\n"
                     L"Pressing the right mouse button on the QR code - context menu.\n"
                     L"Esc - exit from the program.\n\n"
                     L"The program does not require installation, and it works offline.\n\n"
                     L"Nayuki library used in project:\n"
                     L"https://github.com/nayuki/QR-Code-generator\n\n"
                     L"License: MIT License\n\n"
                     L"Author: Aleksey Lonchakov, LonchakovAV@yandex.ru\n"
                     L"June 2019";
    }

    MessageBox( Handle, msg.c_str(), L"SimpleQRCode", MB_ICONINFORMATION );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::FormResize(TObject *Sender)
{
  RepaintQR();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::pu_copyClick(TObject *Sender)
{
  // copy the picture of QR Code into clipboard
  Clipboard()->Assign(ImageQR->Picture);
}
//---------------------------------------------------------------------------
// Generate new picture after changing the text in the memo
void __fastcall TFormSimpleQRCode::Memo1Change(TObject *Sender)
{
  UnicodeString text = Memo1->Lines->Text;
  UnicodeString text_length = IntToStr( text.Length() );
  UnicodeString msg;
  switch(lang)
  {
    case LANG_RUSSIAN: msg = L"Количество символов: " + text_length + ", ширина изображения: "; break;
    default:           msg = L"Symbols: "             + text_length + ", image width: ";
  }
  width_pos = msg.Length();
  StatusBar1->SimpleText = msg;

  try
  {
    // encode text to UTF8 format
    RawByteString s = UTF8Encode(text);

    if(text.Length())
    {
      // generate QR Code
      if(qr)
        *qr = QrCode::encodeText(s.c_str(), QrCode::Ecc::MEDIUM);
      else
        qr = new QrCode( QrCode::encodeText(s.c_str(), QrCode::Ecc::MEDIUM) );
    }
    else
    {
      delete qr;
      qr=NULL;
      StatusBar1->SimpleText = str_type_text;
    }
  }
  catch(...)
  {
    delete qr;
	  qr=NULL;

    switch(lang)
    {
      case LANG_RUSSIAN: msg = L"Ошибка. Возможно, текст слишком большой.\n\n"
                               L"Примерный максимальный размер текста, символов:\n"
                               L" - кириллица 1280\n"
                               L" - латиница 2310\n"
                               L" - цифры 5590";
                               break;

      default:           msg = L"Error. The text may be too long.\n\n"
                               L"Approximate maximum text size, characters:\n"
                               L" - cyrillic and other 1280\n"
                               L" - latin 2310\n"
                               L" - digits 5590";
    }

    FormResize(Sender);
	  MessageBox( Handle, msg.c_str(), L"SimpleQRCode", MB_ICONERROR );
    return;
  }

  // auto scale on first startup
  // next, only by pressing on image with left mouse button
  static bool first_run = true;
  if(first_run)
  {
    first_run = false;
    ImageQRClick(Sender);
  }

  // draw QR Code
  FormResize(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimpleQRCode::ImageQRClick(TObject *Sender)
{
  // auto scale by pressing right mouse button on image
  if(qr && qr->getSize()>0)
  {
    int size = qr->getSize();
    int n = size*8;
    if(n<512) n = 512;
    bool very_big = false;
    int sh = Screen->WorkAreaHeight;
    int sw = Screen->WorkAreaWidth;
    if(n>sh) { n = sh; very_big=true; }
    if(n>sw) { n = sw; very_big=true; }
    Panel2->Height = StatusBar1->Height + (very_big ? 50 : 211);
    SetBounds( Screen->WorkAreaLeft + (sw-n)/2, Screen->WorkAreaTop + (sh-n)/2, n, n );
  }
}
//---------------------------------------------------------------------------
// draw qr on ImageQR
void TFormSimpleQRCode::RepaintQR()
{
  int w = (Panel1->Height<Panel1->Width) ? Panel1->Height*0.95 : Panel1->Width*0.95;
  ImageQR->SetBounds( (Panel1->Width-w)/2, (Panel1->Height-w)/2, w, w );

  ImageQR->Picture->Bitmap->SetSize( ImageQR->Width, ImageQR->Height);

  ImageQR->Canvas->Pen->Style = psClear;
  ImageQR->Canvas->Brush->Style = bsSolid;
  ImageQR->Canvas->Brush->Color = clWhite;
  ImageQR->Canvas->FillRect( Rect(0,0,ImageQR->Width,ImageQR->Height) );

  if(qr && qr->getSize()>0)
  {
    int size = qr->getSize();
    double scale = double(ImageQR->Width) / size;

    for(int y=0; y<size; y++)
    {
      for(int x=0; x<size; x++)
      {
        ImageQR->Canvas->Brush->Color = qr->getModule(x,y) ? clBlack : clWhite;
        ImageQR->Canvas->FillRect( Rect(x*scale,y*scale,(x+1)*scale,(y+1)*scale) );
      }
    }
  }

  // refresh the picture size at status bar
  if(qr && width_pos)
    StatusBar1->SimpleText = StatusBar1->SimpleText.SubString(1,width_pos) + IntToStr( ImageQR->Width );
}
//---------------------------------------------------------------------------

