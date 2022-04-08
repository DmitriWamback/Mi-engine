import core.MiTPY as Mi

a = Mi.MiTPY()
a.attemptConnection()

d = [0, 0, 0, 1,
     0, 1, 0, 2,
     0, 2, 0, 3,
     0, 3, 0, 4,
     0, 4, 0, 15,
     0, 5, 0, 115,
     0, 6, 0, -115]

Mi.MiTPY.formData(d, Mi.MITPY_3D_DATA_TRANSFER)

while 1:
    a.transfer('hello')