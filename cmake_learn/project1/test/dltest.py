

def bb_intersection_over_union(boxA, boxB):
		# boxA : x1,y1,x2,y2 (左上x，左上y，右下x，右下y)
    boxA= [int(x) for x in boxA]
    boxB= [int(x) for x in boxB]

    xA= max(boxA[0], boxB[0])
    yA= max(boxA[1], boxB[1])
    xB= min(boxA[2], boxB[2])
    yB= min(boxA[3], boxB[3])

    interArea= max(0, xB- xA+ 1)* max(0, yB- yA+ 1)

    print(interArea)

    boxAArea= (boxA[2]- boxA[0]+ 1)* (boxA[3]- boxA[1]+ 1)
    boxBArea= (boxB[2]- boxB[0]+ 1)* (boxB[3]- boxB[1]+ 1)

    iou= interArea/ float(boxAArea+ boxBArea- interArea)

    return iou


if __name__ == '__main__':

    boxA = [10,10,20,20]
    boxB = [15,15,25,25]
    print(bb_intersection_over_union(boxA,boxB))