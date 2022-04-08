# MITI directory
<p>MITI, or Mi Transfer Interface, is a sub-module of the Mi Engine to visualize 3D, 2D and 1D data using interactive graphics rendering to display data. The data can be imported via socket clients; the repository: <a>https://github.com/DmitriWamback/mitipy</a> is a python wrapper to send data to display it in the engine.</p>
<p>Data available to send:<p>
<p>Intensity([a]) signifies the weight of that point (should be clamped within [0, 1]). The intensity can be multidimensional to further precise data visualization.</p>
<ul>
    <li>1D data: {intensity(x), intensity(x)...}</li>
    <li>2D data: {intensity(x, y), intensity(x, y)...}</li>
    <li>3D data: {intensity(x, y, z), intensity(x, y, z)...}</li>
</ul>
