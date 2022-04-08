import socket
import time
import datetime

MITPY_2D_DATA_TRANSFER          = 0x01
MITPY_3D_DATA_TRANSFER          = 0x02
MITPY_1D_DATA_TRANSFER          = 0x03

ATTR = {
    MITPY_1D_DATA_TRANSFER: 2,
    MITPY_2D_DATA_TRANSFER: 3,
    MITPY_3D_DATA_TRANSFER: 4
}

class MiTPY:

    def __init__(self):
        # Default Mi transfer p 
        self.addr = {'addr': 'localhost',
                     'port': 6060       }

        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def attemptConnection(self) -> bool:
        try:
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client.connect((self.addr['addr'], self.addr['port']))
            print('Connection succeeded!')
            return True
        except:
            print(f'[{str(datetime.datetime.now())}] Connection attempt failed, reconnecting...')
            time.sleep(0.5)
        return False

    def transfer(self, data):
        try:
            self.client.send(str(datetime.datetime.now()).encode())
            time.sleep(0.01)
        except:
            print(f'[{str(datetime.datetime.now())}] Error: Connection halted! reconnecting...')
            while 1:
                if self.attemptConnection() == True:
                    break

    def _toDType(self, data, d_type):

        pass

    def formDataToStringify(data, d_type: int) -> str:
        
        attr = ATTR[d_type]
        v = int(len(data)/attr)

        weights = []                        # data array for intensities
        points = []

        # FINDING DEFAULT WEIGHTS AND POSITIONS
        for i in range(v):
            index = attr*(i+1)-1
            weight = data[index]

            points.append([data[index-3], data[index-2], data[index-1]])

            weights.append(weight)

        # FINDING WEIGHT EXTREMITIES (min and max)
        minimum_extremity = weights[0]
        maximum_extremity = weights[0]

        for i in range(v):                  # finding both the maximum and minimum intensities from the data
            if weights[i] < minimum_extremity:
                minimum_extremity = weights[i]

            if weights[i] > maximum_extremity:
                maximum_extremity = weights[i]

        maximum_extremity += abs(minimum_extremity)

        # AVERAGING WEIGHTS
        for i in range(v):                  # averaging weights
            weights[i] += abs(minimum_extremity)
            weights[i] = weights[i]/maximum_extremity   
        pointWeightData = []                # data array for posiitons and weights

        for i in range(v):                  # appending the points and weights to the same array
            pointWeightData.append(points[i])
            pointWeightData.append(weights[i])

        stringifiedData = f'[DTYPE: {str(d_type)}]: '

        # TURNING DATA TO STRING
        for i in range(int(len(pointWeightData)/2)):
            
            currentPoint = pointWeightData[i*2]
            currentWeight = pointWeightData[i*2+1]

            stringifiedData += str(currentPoint) + ' ' + str(currentWeight) + ', '

        return stringifiedData