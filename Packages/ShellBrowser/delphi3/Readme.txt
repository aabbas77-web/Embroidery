                        S H E L L B R O W S E R
                       =========================
                      2.3 for Delphi / C++ Builder


The ShellBrowser component set gives a Delphi programmer easy access to the
Win32 shell functionality. The TJamShellList, TJamShellTree and TJamShellCombo
components look and behave exactly like the corresponDing parts of the Explorer
The TShellBrowser component provides an easy interface to the Windows shell. 
For any object all components can show the explorer context menu, the
properties page, the correct item and much more. You can shuffle the explorer
context menu with your own Delphi popup menus and OLE drag&drop operations are
supported. This makes it very easy to add typical Win9x functionality to your
existing applications and allows you build an Explorer like application with
only a few lines of code. Interesting sample projects and help file with a lot
of sample code are included.


INSTALLATION
~~~~~~~~~~~~
After installing the package JamShell via Components|Install Packages in
the IDE, you will find a new tab "JAM Software" in the component palette,
which contains the shell components. Then you should have a look at the sample
applications included. 
Since Delphi doesn't add the path to new packages automatically to the search
path, you may need to add the path of the Lib folder of ShellBrowser to the 
library path in the Environment Options of Delphi and C++ Builder. Please have
a look at the file Readme.txt in the Help directory to get information how to
install the help files of the ShellBrowser components. C++ Builder 5 users:
please read the next section.


KNOWN PROBLEMS
~~~~~~~~~~~~~~
* C++ Builder 5 users: Due to some obscure changes that Borland has done on the
  shell header files, you have to add the conditional define 
  NO_WIN32_LEAN_AND_MEAN to your project options. Otherwise some relevant parts
  of the shell header files will not be included and your project won't compile.
* On some old Windows 95 versions incorrect drag&drop cursors may be shown.
* If you get an error message like "Fatal Error: File not Found: ShellBrowser.dcu"
  during compilation, you din't include the path of ShellBrowser to the library
  path of Delphi. Please see section "Installation".
Please report all bugs and problems you have to the e-Mail adress below.


COPYRIGHT
~~~~~~~~~
The ShellBrowser components are Shareware, that means you can try them and
may distribute the complete archive of the trial version. If you decide to use
them, you must register. Please look in the help file for detailed registration
information.
                                      Copyriht ©1997-2000 by Joachim Marder

CONTACT
~~~~~~~
JAM Software
Joachim Marder
Südallee 35
54290 Trier
Germany

E-Mail  : support@jam-software.com
WWW-Page: http://www.jam-software.com/delphi/
Fax     : +49-700-70707059


CHANGES
~~~~~~~
V2.3: Released on 19 Mar 2001
* Added the method InvokeCommandOnFolder to the TJamShellList, which allows to
  invoke a context menu command like "paste" on the curently listed folder. This
  is e.g. useful for moving or copying files from one TJamShellList to another.
* Added a new event TOnContextMenuSelect to the components TShellBrowser,
  TJamShellList and TJamShellTree, which is fired when the user has selected
  an item of the context menu.
* Double clicking on a shortcut to a folder in the TJamShellList now switches
  to this folder. New method IsLinkToFolder method in TShellBorwser.
* Like in the Explorer, Shift+F10 now shows the context menu
* New property BackgroundPopupMenu in TJAmShellListView: If the user doesn't hit
  an item with a right click, this Popup menu is shown.
* New property Filter for TJamShellTree to filter the files when ShowFiles is
  True.
* New 'function GetMyDocumentsPath: String' in ShellBrowser.pas for easier
  access to the path of the My Documents folder.
* Fixed problem: When deleting a file in the TJamShellTree, sometimes an Access
  Violation occured.
* Items that have been added manually to the TJamShellTree, caused  an access
  violation when shutting down the application. This has been fixed.
* The TJamShellTree now shows the hand icon for shared folders.
* You can now use the Add method of TJAmShellList.SelectedFiles to add files to
  the selection in a TJamShellList control.
* If the ReadOnly property is set to True, it also prevents delete, cut and
  paste operations from being executed.
* When the SelectedFolder property was set to a network path, previous versions
  of TJamShellTree didn't select the correct network folder. 
* Several minor bug fixes

V2.2: Released 11 Aug 2000
* New method CreateDir for TJamShellTree, which creates a new folder and lets
  the user edit the name.
* The method CreateDir of the TJamShellListView now has an additional boolean
  argument EditMode which can be used to allow the user to edit the name of the
  newly created folder.
* New event OnOperation for TJamShellTree and TJAmShellList that informs about
  shell operations that affect the shell controls. Please have a look in the
  help file for details.
* The TJamShellTree has a new boolean property ShowFiles which allows you to
  show the files in the Tree, like in Frontpage 2000.
* New boolean property ShowNetHood for TJamShellTree
* New methoed GetFullpath which returns the path for a given TTreeNode.
* Added AutoExpand feature during Drag&Drop operations to a TJamShellTree.
* The SelectedFiles property of the TJamShellListView didn't update its content
  in the previous version if the user changed the selection using the keyboard.
* Setting ReadOnly to True didn't disable renaming of files and folders
* The columns in the Report mode of the TJamShellListView didn't always show the
  correct information.
* Expanding a folder in the TJAmShellTree is faster now.

V2.1: Released 28 Jan 2000
* A bug in the TJamShellcombo is fixed, which sometimes caused error messages
* TJamShellCombo did not work correct with network folders
* Added the method IsSpecialObject to TShellBrowser
* TJamSystemImageList.GetIconFromExtension did not work correctly
* Better Dag&Drop support, e.g. for selected text
* Added method CreateDir to TJamShellList
* Added properties ShowHidden and FileSystemOnly (like they exist for the
  TJAmShellList) to the TJamShellTree. You can use them e.g. to hide the
  Recycled folders.
* Added AutoScroll feature during Drag&Drop operations to JamShellTree and
  TJamShellList
* Several minor bug fixes and improvements

V2.0 final: Released on 07 Jul 1999
* The TJamShellListView now has a property SelectedFiles, which is a TStringList
  with the currently selected folders and files, including their extension.
* The method ShowContextMenu of TJamShellList and TJamShellTree now returns the
  performed command, see help file for details.
* The mothod GetFolderIconNumber has been added to the TJamSystemImageList and
  returns the number of the standard folder icon.
* Some additional special folders have been added to the TJamShellFolder type.
* Some minor bug fixes

V2.0 beta 3: Released on 21 May 1999
* The new component TJamSystemImageList replaces the SmallImages and LargeImages
  properties of the TShellBrowser component. This change was necessary, because
  Delphi compiled the complete system image list into the executable. You will
  need to change your projects in the following way: Replace each ImageList
  assigned to a TShellBrowser component with a TSystemImageList and set the Images
  property of ListViews and TreeViews again.
* You can use the GetIndexFromExtension method of the TJamSystemImageList to
  get the icon number for a certain extension.
* Ole Drag&Drop is now implemented and seems to work fine. Use the property
  OleDragDrop to enable or disable it.
* The components had problems with the Drag & Dock operations of Delphi 4, this
  is fixed now.
* The TJamShellList component has a ShowHidden property now.
* A property ShellContextMenu lets you determine if the shell context menu
  should be displayed automatically when the user right clicks on a file or
  folder.
* A problem with the TJamShellCombo component is fixed now, sometimes the
  entries were not displayed in the correct order.

V2.0 beta 2: Released on 24 Mar 1999
* Help file is complete now.
* New methods GetColumnText and GetColumnInfo for the TShellBrowser component,
  which allow to get information what Explorer would display in a certain
  column for a certain file.
* Only those part of a TJamShellList is filled, which is visible to the user.
  The   rest is filled on demand. This speeds up filling of a TJamShellList.
* Like in the Windows Explorer, refreshes are delayed if the user selected a
  new folder using the keyboard. This makes use of the keyboard smarter in the
  TJamShellTree.
* Now runs with Delphi 4.00 - 4.03
* Several bug fixes and improvements
* Drag & Drop support is still missing (Sorry!), but will be present in the next
  release (Promised!)

V2.0 beta 1: Released 06 Feb 1999
* New visible Explorer like controls TJamShellTree, TJamShellList and
  TJamShellCombo were added
* New invisble component TJamShellLink which allow to synchronize the above
  components
* TShellBrowser now has a Filter property which allows to filter certain files
* TShellBrowser has an Event OnFileChanged which is fired when a change (adding,
  renaming or deleting of files) occured in the current directory.
* You can test with the IsSpecialFolder method, if the current folder is a
  special folder, e.g. the Control PAnel
* ShellBrowser now shows 'Rename' in the context menu and fires the event
  OnRename when this menu item is selected
* A lot of small but useful enhancements and bug fixes

V1.01: Released 03 Jul 98
* Support for Borland C++ Builder 3
* Problem fixed, that caused the Cut/Copy context menu items not to work on
  some Windows 95 versions.
* Problem fixed in the InvokeContextMenuCommand method, which sometimes 
  produced an error when used with mutiple files.
* Two small problems fixed in the Advanced sample

V1.0 (final release): Released 04 Jun 98
