from operator import truediv
from pyvis.network import Network 
import pandas as pd



# Just a small function to check wether the 
# arc is in the solution or not.

def is_in_path(src, dst, path):
    for couple in path:
        if (couple[0] == src) and (couple[1] == dst):
            return True
        else:
            return False



# The code in itself

net = Network(height='750px', width='100%',  bgcolor='#003333',font_color='white')

# set the physics layout of the network
net.barnes_hut()

data = pd.read_csv('exemple1.csv')

num1 = data['Num1']
num2 = data['Num2']
x1 = data['x1']
y1 = data['y1']
x2 = data['x2']
y2 = data['y2']
temps_min = data['temps_min']
temps_max = data['temps_max']


arc_data = zip(num1, num2, x1, y1, x2, y2, temps_min, temps_max)

solution = pd.read_csv('solution_test.csv')

src = solution['Src']
dst = solution['Dst']

path_solution = zip(src, dst)

for arc in arc_data:
    src = str(arc[0])
    dst = str(arc[1])
    w = (arc[7] - arc[6])

    net.add_node(src, title = src, color = "FFE920")
    net.add_node(dst, title = dst, color = "FFE920")

    if is_in_path(arc[0], arc[1], path_solution):
        net.add_edge(src, dst, value = w, color="F9BB00")
    else:
        net.add_edge(src, dst, value = w, color="FFF284")

#neighbor_map = net.get_adj_list()

# add neighbor data to node hover data
#for node in net.nodes:
#    node['title'] += ' Neighbors:<br>' + '<br>'.join(neighbor_map[node['id']])
#    node['value'] = len(neighbor_map[node['id']])

net.show("essai.html")
quit()
