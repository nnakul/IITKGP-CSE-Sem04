
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from PIL import Image
import numpy as np
from random import random

def plot_boxes ( image , pred_boxes , pred_classes , save_as , output_loc , annotation_type = 'top' , limit_boxes = 5 ) :
  
  image = image.swapaxes(0, 1).swapaxes(1, 2) * 255
  image = np.around(image)
  fig, ax = plt.subplots(1)
  ax.imshow(image.astype(np.uint8))
  
  colours = ['#DC143C', '#FFD700', '#FF4500', '#0033CC', '#800080']
  count = 0
  
  if annotation_type == 'adjust' :
    type = 0
    for j in pred_boxes :
        if count == limit_boxes : break
        left = j[0][0]
        width = j[1][0] - left
        height = j[1][1] - j[0][1]
        top = j[0][1]
        bottom = height + top

        rect = patches.Rectangle((left,top),width,height,linewidth=2,edgecolor=colours[count%5],facecolor='none')
        ax.add_patch(rect)
        if type == 0 :
          ax.annotate(pred_classes[count],xy=(left,top),color=colours[count%5],ha='left',va='bottom',size=10,weight='bold')
        elif type == 1 :
          ax.annotate(pred_classes[count],xy=(left,bottom-2),color=colours[count%5],ha='left',va='bottom',size=10,weight='bold')
        elif type == 2 :
          ax.annotate(pred_classes[count],xy=(left+width,top),color=colours[count%5],ha='right',va='bottom',size=10,weight='bold')
        else :
          ax.annotate(pred_classes[count],xy=(left+width,bottom-2),color=colours[count%5],ha='right',va='bottom',size=10,weight='bold')
        type = ( type + 1 ) % 4
        count += 1
  
  else :
    for j in pred_boxes :
      if count == limit_boxes : break
      left = j[0][0]
      width = j[1][0] - left
      height = j[1][1] - j[0][1]
      top = j[0][1]
      bottom = height + top

      rect = patches.Rectangle((left,top),width,height,linewidth=2,edgecolor=colours[count%5],facecolor='none')
      ax.add_patch(rect)
      if annotation_type == 'top' :
        ax.annotate(pred_classes[count],xy=(left+width*random(),top),color=colours[count%5],ha='center',va='bottom',size=10,weight='bold')
      else :
        ax.annotate(pred_classes[count],xy=(left+width*random(),bottom-2),color=colours[count%5],ha='center',va='bottom',size=10,weight='bold')
      count += 1

  plt.savefig( output_loc + '/' + save_as )
