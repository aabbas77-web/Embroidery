{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit                    }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

{-$DEFINE VRSHARE}

{$B-} { Complete Boolean Evaluation }
{$R-} { Range-Checking }
{$V-} { Var-String Checking }
{$I-} { IO Checking }
{$Q-} { Overflow checking }


{$IFDEF VER130}
  {$DEFINE VER120}
{$ENDIF}

{$IFDEF VER125}
  {$DEFINE VER110}
{$ENDIF}

{$IFDEF VER120}
  {$DEFINE VER110}
{$ENDIF}

{$IFDEF VER110}
  {$DEFINE VER100}
{$ENDIF}

