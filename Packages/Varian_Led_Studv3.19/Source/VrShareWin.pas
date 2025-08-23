{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrShareWin;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, VrConst;

type
  TForm_VrShare = class(TForm)
    OkButton: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Image3: TImage;
    Bevel1: TBevel;
    Image1: TImage;
    procedure FormCreate(Sender: TObject);
    procedure OkButtonClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

procedure ShowRegWin;

implementation

{$R *.DFM}

var
  Form_Share: TForm_VrShare;


procedure ShowRegWin;
begin
  if Form_Share.Tag = 0 then
  begin
    Form_Share.ShowModal;
    Form_Share.Tag := 1;
  end;
end;


procedure TForm_VrShare.FormCreate(Sender: TObject);
begin
  Caption := 'About Varian Led Studio';
  Label3.Caption := 'Version '+ VrLibVersion + #13 + '(c) Varian Software NL';
  Label1.Caption := 'Thank you for evaluating Varian Led Studio ' + VrLibVersion + '...';
  Label2.Caption := 'This is not free software. You are hereby allowed '+
                    'to use this software for evaluation purposes without '+
                    'charge for a period of 30 days. If you use this software '+
                    'after the 30 day evaluation period a registration fee is '+
                    'required. See the enclosed documentation for more info '+
                    'on how to register.';

end;

procedure TForm_VrShare.OkButtonClick(Sender: TObject);
begin
  Close;
end;


initialization
  Form_Share := TForm_VrShare.Create(nil);

finalization
  Form_Share.Free;


end.
