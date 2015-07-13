import numpy as np
import cv2
import threading
cap = cv2.VideoCapture('sample.3gp')
cap1 = cv2.VideoCapture('sample.3gp')
cap2 = cv2.VideoCapture('sample.3gp')
cap3 = cv2.VideoCapture('sample.3gp')
fps=cap.get(5)
no_thd=cap.get(7)
b=no_thd/4
cap1.set(1,b)
cap2.set(1,2*b)
cap3.set(1,3*b)
out = cv2.VideoWriter('output.avi',-1, 8, (176,144))
out1 = cv2.VideoWriter('output1.avi',-1, 8, (176,144))
out2 = cv2.VideoWriter('output2.avi',-1, 8, (176,144))
out3 = cv2.VideoWriter('output3.avi',-1, 8, (176,144))
out4 = cv2.VideoWriter('output4.avi',-1, 8, (176,144))
class myThread (threading.Thread):
    def __init__(self, threadID, name, vid_class, vid_out,v,x):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name 
        self.vid_class=vid_class
        self.vid_out=vid_out	
        self.v=v
        self.lst_frm=x		
		
		
    def run(self):
        print "Starting " + self.name
        print self.vid_class.get(1)
        while(self.lst_frm!=self.vid_class.get(1)):
          ret, frame = self.vid_class.read()
          if ret==True:
          #k = cv2.flip(frame,1)
           grey=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
           #ret1,thresh1=cv2.threshold(frame,127,255,cv2.THRESH_BINARY)
           #thresh3=cv2.adaptiveThreshold(grey,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,11,2)
		   #print frame.shape

           # write the flipped frame
           self.vid_out.write(grey)
           #cv2.imshow(self.v,frame)
           #if cv2.waitKey(25) & 0xFF == ord('q'):
             #break

          #cv2.imshow('video',grey)
		
# Create new threads
thread1 = myThread(1, "Thread-1", cap, out1,'v1',b)
thread2 = myThread(2, "Thread-2", cap1, out2,'v2',2*b)
thread3 = myThread(3, "Thread-3", cap2, out3,'v3',3*b)
thread4 = myThread(4, "Thread-4", cap3, out4,'v4',no_thd)

threads=[]

# Start new Threads
thread1.start()
thread2.start()
thread3.start()
thread4.start()

# Add threads to thread list
threads.append(thread1)
threads.append(thread2)
threads.append(thread3)
threads.append(thread4)

# Wait for all threads to complete
for t in threads:
    t.join()
cap.release()
cap1.release()
cap2.release()
cap3.release()
out1.release()
out2.release()
out3.release()
out4.release()

videofiles = ['output1.avi','output2.avi','output3.avi','output4.avi']
#videofiles = sorted(videofiles, key=lambda item: int( item.partition('.')[0][3:]))
 
video_index = 0
capx = cv2.VideoCapture(videofiles[0])
 
# video resolution: 1624x1234 px
#out = cv2.VideoWriter("output.avi", -1,8.0, (176,144))
 
while(capx.isOpened()):
    ret, frame = capx.read()
    if frame is None:
        print "end of video " + str(video_index) + " .. next one now"
        video_index += 1
        if video_index >= len(videofiles):
            break
        capx = cv2.VideoCapture(videofiles[ video_index ])
        ret, frame = capx.read()
    #cv2.imshow('final',frame)
    out.write(frame)
    #if cv2.waitKey(1) & 0xFF == ord('q'):
       # break
 
capx.release()
out.release()
 
print "end."
print "Exiting Main Thread"





