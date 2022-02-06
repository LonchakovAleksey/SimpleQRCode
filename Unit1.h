//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "QrCode.hpp"  // Nayuki
//---------------------------------------------------------------------------
class TFormSimpleQRCode : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TImage *ImageQR;
  TPopupMenu *PopupMenu1;
  TMenuItem *pu_copy;
  TPanel *Panel2;
  TMemo *Memo1;
  TStatusBar *StatusBar1;
  void __fastcall Memo1Change(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall pu_copyClick(TObject *Sender);
  void __fastcall ImageQRClick(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
  __fastcall TFormSimpleQRCode(TComponent* Owner);

  qrcodegen::QrCode *qr;  // the generated QR is stored in memory for its redrawing when resizing the form

  int lang;       // language for translate
  int width_pos;  // position in status bar for insert image width
  UnicodeString str_type_text;  // status bar text while memo is empty

  void RepaintQR();  // paint stored QR
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleQRCode *FormSimpleQRCode;
//---------------------------------------------------------------------------
#endif
