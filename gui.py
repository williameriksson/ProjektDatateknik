from subprocess import call
from threading import Thread
import Tkinter as tk
import time
import urllib
import urlparse

GRID_W = "500"
GRID_H = "500"

class Gui():
   def __init__(self, GRID_W, GRID_H):
      self.root = tk.Tk()
      self.root.title("Camera settings")
      self.root.geometry(GRID_W + "x" + GRID_H)
      self.canvas = tk.Canvas(self.root, width=int(GRID_W), height=int(GRID_H), borderwidth=0,  highlightthickness=0, bg="black")
      self.canvas.grid()
      self.b = tk.Button(self.canvas, text="Button1", command=self.button_1)
      self.b.pack()
      self.root.mainloop()


   def onKeyPress(self, event):
       x = event.char
       if x == "d":
	  print "d"
          #self.canvas.move(a, 2, 0)
       elif x == "a":
          print "a"
          #self.canvas.move(a, -2, 0)
       elif x == "w":
          print "w"
          #self.canvas.move(a, 0, -2)
       elif x == "s":
          print "s"
          #self.canvas.move(a, 0, 2)

   def button_1(self):
      try:
         self.url = "http://192.168.10.4/set?casino_mode=on"
         self.url_parts = list(urlparse.urlparse(self.url))
         

         #self.httpServ = httplib.HTTPConnection("192.168.10.4", 80, timeout=5)
         #self.httpServ.connect()
         #self.httpServ.request('POST', "set?casino_mode=on")
         #self.httpServ.close()
      except Exception as e:
         print (type(e))



   #root.bind_all('<Key>', onKeyPress)




gui_1 = Gui(GRID_W, GRID_H)
thread_1 = Thread(target = gui_1)
thread_1.start()
#thread_2 = Thread(call(["./mixerh264", "0", "0", "0"]))
#thread_2.start()


