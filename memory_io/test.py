import yaml


with open("example_memory_map.yaml", 'r') as stream:
    data_loaded = yaml.safe_load(stream)
print(data_loaded)
