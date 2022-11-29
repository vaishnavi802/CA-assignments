import sys
import numpy as np
import matplotlib.pyplot as plt
from skimage import exposure as ex
import cv2
from mpi4py import MPI


frequency = []
# MPI Functions
comm = MPI.COMM_WORLD
processor = comm.Get_size()
rank = comm.Get_rank()

print(rank)
    
def saveImage(img):
    """
    Open the image in matplotlib and save it.
    """

    # Grey scale image
    number_of_pix = np.sum(img) 
    print('Number of pixels : ', number_of_pix)
    
    plt.imshow(img)
    plt.imsave('inp.jpg', img)
    plt.show()

    # Histogram of the image
    histr = cv2.calcHist([img], [0], None, [256], [0,256])
    plt.plot(histr)
    plt.imsave('New_image.jpg', histr)
    plt.show()
    
    return

def frequency(img):
    """
    Saving the frequency of pixels, PDF and CDF.
    """
    (x,y) = img.shape
    print(x,y)

    freq=[0]*256;
    size = x*y
    numOfPix = np.sum(img);

    temp=0;

    # Frequency of pixels
    for i in range(0,x):
        for j in range(0,y):
            temp = img[i][j];
            freq[temp]+=1

    # Saving the frequency of pixels in a file
    with open('frequency.txt', 'w') as f:
        for item in freq:
            f.write("%s " % item)

    # # Print the frequency of pixels
    # print("Frequency of pixels :")
    # for i in freq:
    #     print(i);

    # PDF - Probability Density Function of the image            
    pdf = []
    for i in freq:
        pdf.append(i/size)

    # Saving the PDF in a file
    with open('pdf.txt', 'w') as f:
        for item in pdf:
            f.write("%s " % item)

    # CDF - Cumulative Density Function of the image        
    cdf = []
    total = 0
    for i in pdf:
        total=total+i
        cdf.append(total)
    
    # Saving the CDF in a file
    with open('cdf.txt', 'w') as f:
        for item in cdf:
            f.write("%s " % item)

    tr = []
    for i in cdf:
        t = round(i*255)
        tr.append(t)
        
    print("PDF: ", pdf, "\tCDF: ", cdf, "\tTR: ", tr)

    pixels = []

    for i in range(256):
        pixels.append(x)
        
    hs = []
    for i in pixels:
        count=0
        tot=0
        for j in tr:
            if(j==i):
                tot=tot+freq[count];
            count+=1

        hs.append(tot)
    return hs

def equilize(img):
    """
    Equalize the image and save it.
    """

    # Equalize the image
    result = grey(img)
    plt.imshow(result)
    plt.imsave('equilise.jpg', result)
    plt.show()

    # Histogram of the equalized image
    histr = cv2.calcHist([result], [0], None, [256], [0,256])
    plt.plot(histr)
    plt.imsave('new.jpeg', histr)
    plt.show()
    return 


def grey(img):
    """
    Convert the image to grey scale.
    """
    outImg = ex.equalize_hist(img[:, :])*255

    outImg[outImg > 255] = 255
    outImg[outImg < 0] = 0

    return outImg.astype(np.uint8)

def main():
    # Taking image as input using mpiexec -n 1 python3 last.py wargames.jpg
    print(sys.argv)
    img = cv2.imread(sys.argv[1],0)
    height, width = img.shape
    
    size = width*height

    if rank == 1 :
        print("Rank 1")
        print("Sending image to rank 0")
        comm.send(saveImage(img), dest=0)
    
    if rank == 2 :
        print("Rank 2")
        print("Sending image to rank 0")
        comm.send(frequency(img), dest=0)

    if rank == 3 :
        print("Rank 3")
        print("Sending image to rank 0")
        comm.send(equilize(img), dest=0)

    else:
        print("Rank 0")
        for procid in range(1, processor):
            message = comm.recv(source=procid)
            plt.show()
            print("Process 0 received message from process" , processor, message);
    
    MPI.Finalize();
        
if __name__ == '__main__':
    main();
