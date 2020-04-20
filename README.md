#Management-GUI-Application

The project above you is a partly done GUI management interface meant to be used in hotel management system application. 

It is developed in C++ 11 programming language with the help of Qt framework.

 ## If you want to run the application and test it on your machine (assuming that it runs Windows) download the .zip file here - [Application_Executable.zip](https://github.com/1000p/Qt-C-Management-GUI-Application/blob/master/Application-Executable.zip)

In this current version I had successfully developed the main window for the project.
 The window is composed of these components:
 
 * A sidebar which purpose will be as of a "toolbox" for the program
 
 * The "work" area of the program - where the rooms are displayed as buttons - each button respresents a room.
 
 * A create new "room" button, located in the sidebar which creates a new room and displays it in the 
 work area of the program - infinate amound of rooms can be displayed.
 
* The work area layout is a flow type that means - resizing the window will rearrange the buttons.
 
 * The rooms are saved to a file upon exiting the program.
 
   * Each room button can open a separate window for it's room. If the "room window" is open pressing again on the "room button" 
   will try to close that window. If there are any changes made a message box will appear asking for action.
      
I have also added some functuallity:

Developed the room window as a form of communication with the user.
That said window consists of:

* Room name - which can be edited.
* Occupants text edit field - that accepts rich text. 
* Notes text edit field - that accepts rich text.
* A check box to reserve the said room. That changes the corresponding button to be red for reserved.
* Cancel button - if there are any changes a message box will appear to save/discard(which will return the changes back to the original values) or cancel the action. If there are no changes made this button exits the window.
* Save button - if there are any changes a message box will appear to save/discard(which will return the changes back to the original values) or cancel the action. If there are no changes made this button does nothing.
* If you try to exit the window and there are changes a message box will appear to save/discard(which will return the changes back to the original values) or cancel the action.

Any of the fields in the window are saved to .txt files, so no information is lost upon exiting the application. 

