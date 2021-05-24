


def getPhidgetData():
    phidget_data_file = open("phidgetdata.txt")
    data = phidget_data_file.read().split(',');
    x = data[::4]
    y = data[1::4]
    z = data[2::4]
    time = data[3::4]
    print(data)


getPhidgetData()
