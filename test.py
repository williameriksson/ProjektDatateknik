from subprocess import call
import thread
import time

def printer(hej, tjena):
   x=0
   while x < 1000:
	time.sleep(0.1)
   	print "HEJHEJHEJHEJHEJHEHEHEHEHJEHJEHJEHJJEHHJEHJEHJEJHEJHEHJEJHEJH"
	x+=1
thread.start_new_thread(printer, (0,0))
time.sleep(1)
thread.start_new_thread(call(["./mixerh264", "0", "0", "0"]))



