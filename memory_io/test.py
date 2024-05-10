import yaml
from dataclasses import dataclass

@dataclass
class Variable():
    name: str
    size: int
    defined = []
    
    def __init__(self, variable: dict):
        self.name = list(variable.keys())[0]


with open("example_memory_map.yaml", 'r') as stream:
    data = yaml.safe_load(stream)

print(data)


for variable in data["parameters"]:
    print(variable) 
    something = Variable(variable, size=variable["size"])
    print(something)