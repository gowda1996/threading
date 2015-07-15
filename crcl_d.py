import cv2
import numpy as np

img1= cv2.imread('houghcircles.png')
img = cv2.imread('houghcircles.png',0)
img = cv2.GaussianBlur(img,(9,9),0)

circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1.2,70,
                            param1=130,param2=83,minRadius=1,maxRadius=189)

circles = np.uint16(np.around(circles))
for i in circles[0,:]:
    cv2.circle(img1,(i[0],i[1]),i[2],(0,255,0),2)
    cv2.circle(img1,(i[0],i[1]),2,(0,0,255),3)

cv2.imshow('circles',img1)
cv2.waitKey(0)
cv2.destroyAllWindows()