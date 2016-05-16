1.For Marathron the Imagebuffer is Shared buffer,
  Two ImageBufferMltiROI(DRAM) is used, each write speed is 1.6GB/s
2.The Parallesim for Camera output link is 8 or 16, 
  If set to 4 ,the image acq will error 
3.Image_bffer_JPEG can not be used by the Marathron by now ,
  but sort can take place of it .
4.the Jpeg output Parallesim changed to 4, and the bitwidth is 8bit ,
   So the BytePerPixel should be 1 for SDK 
5.The image size is 2560*2048 ,so the output size of Jpeg should be more than 524800£¬
   100000000 is eough.
