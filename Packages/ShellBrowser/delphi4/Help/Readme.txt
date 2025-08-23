
  D E L P H I   3
 =================

Delphi 3 users should copy these three files into their Delphi 3\Help
directory. Locate the 'delphi3.cfg' file and add the following line
to the end of the file:

   :link ShellBrowser.hlp

If you also want the contents to appear in the Delphi help system you
should also add the following line:

   :include ShellBrowser.cnt

Finally, delete the hidden file 'delphi3.gid', which will make Delphi rebuild
its contents.



  D E L P H I   4,   C + +   B U I L D E R 
 ==========================================

Delphi4 and C++Builder users should use the OpenHelp utility (Help->Customize
in the IDE) to install the ShellBrowser help files into the IDE help system.
Unfortunately the OpenHelp utility provided by Borland/Inprise doesn't seem to
work very well. But the way described for Delphi 3 still works under Delphi 4.