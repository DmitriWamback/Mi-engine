path = 'src/scenes/data/scene1.mis'

def find_block(lines, name: str):

    START = 0
    FOUND_START = False
    END = 0

    for i in range(len(lines)):
        line = lines[i]
        if line.startswith(name):
            START = i
            FOUND_START = True

        if line == '] <-' and FOUND_START == True:
            END = i
            break

    return START, END

def find_sub_blocks(lines, start, end):

    block_boundaries = []
    t_start = 0
    for i in range(start+1, end):
        line = lines[i]
        if '{' in line:
            t_start = i+1

        if '}' in line:
            block_boundaries.append([t_start, i])
            t_start = 0

    return block_boundaries

def find_attribute_in_block(lines, attrib, start, end):
    
    attrib_value = None

    for i in range(start, end):
        
        if f'{attrib}: ' in lines[i]:
            _attrib = lines[i].split(f'{attrib}: ')[1].replace('"', '')
            attrib_value = _attrib

    return attrib_value


with open(path, 'r+') as f:
    lines = f.readlines()

    for i in range(len(lines)):
        lines[i] = lines[i].replace('\n', '')

    SCENE_NAME = None
    for i in range(len(lines)):
        line = lines[i]
        if line == '[SCENE]':
            SCENE_NAME = lines[i+1].split('name: ')[1].replace('"', '').replace('\n', '')

    SHADER_BLOCK_START, SHADER_BLOCK_END = find_block(lines, 'shaders')
    BLOCKS = find_sub_blocks(lines, SHADER_BLOCK_START, SHADER_BLOCK_END)

    for i in range(len(BLOCKS)):

        block_start = BLOCKS[i][0]
        block_end   = BLOCKS[i][1]

        shaderName = find_attribute_in_block(lines, 'name', block_start, block_end)
        shaderVPath = find_attribute_in_block(lines, 'vsp', block_start, block_end)
        shaderFPath = find_attribute_in_block(lines, 'fsp', block_start, block_end)
        shaderType = find_attribute_in_block(lines, 'type', block_start, block_end)

    ENTITIES_BLOCK_START, ENTITIES_BLOCK_END = find_block(lines, 'entities')
    BLOCKS = find_sub_blocks(lines, ENTITIES_BLOCK_START, ENTITIES_BLOCK_END)

    for i in range(len(BLOCKS)):

        block_start = BLOCKS[i][0]
        block_end   = BLOCKS[i][1]

        position  = find_attribute_in_block(lines, 'position',  block_start, block_end)
        rotation  = find_attribute_in_block(lines, 'rotation',  block_start, block_end)
        scale     = find_attribute_in_block(lines, 'scale',     block_start, block_end)
        type      = find_attribute_in_block(lines, 'type',      block_start, block_end)
        instanced = find_attribute_in_block(lines, 'instanced', block_start, block_end)

        print(position)
        print(type)
        print(instanced)