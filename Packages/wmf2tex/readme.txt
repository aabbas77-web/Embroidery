WMF, EMF, EPS and TEX
-----------------------
(c) 1999 Lucian Wischik


The program here was intended to take Windows clipboard
graphics and convert them to EPS or EPIC code, suitable
for inclusion in the Tex document preparation system.
I never finished it. Instead I'm making the source code public
and freely usable, without restriction, in the hope that
it may benefit some other developers. The program was originally
written for BCB4. I haven't tried it with other versions
of BCB, but don't expect problems. The first thing you should
try doing is compiling the wmfeps_utils package and installing it.



TRealMetafile
---------------

This component stores a metafile. It lets you play back
the metafile record by record, or play it into a canvas
or another metafile. Why do we need this? Why can't we
just use Borland's TMetafile component?

- TRealMetafile knows whether it was given a wmf or
  an emf, and respects that. By contrast, TMetafile
  seemed to convert everything into a wmf (or was
  it the other way round?) so losing precision.

- TRealMetafile lets you play through the metafile
  record by record. This is useful if you want to convert
  the metafile into your own, different graphics format.

- I never managed to get the millimetre dimensions from
  TMetafile to work correctly. You can see precisely
  what's up with the TRealMetafile.

The component's properties and methods are described in
the file wmfeps_utils_RealMeta.h and are implemented in
the corresponding .cpp file. In fact, wmfeps_utils makes
up a package that you should build separately and then
install.



Other useful bits and pieces
------------------------------

- EpsGen component. Given a metafile, this component
  generates a .EPS (embedded postscript) file.
  Implemented in wmfeps_utils_EpsGen.cpp,
  with properties and methods in wmfeps_utils_EpsGen.h,
  part of the wmfeps_utils package.

- StripLatex, in f_gen.cpp. This routine takes in a metafile
  and removes all the text that was in a particular font.

- I also wrote code which converts (badly) a metafile
  into a picture in tex's Epic picture language. But I
  can't find the code anywhere. Oh well.



All this code was written years ago and I've forgotten most of it.
If you have any questions I'll do my best to answer, but probably
won't be of much help. -- Lucian.  http://www.wischik.com/lu


