'''
Created on Feb 25, 2018

@author: copernicus
'''
import jinja2
import avro.schema
from sets import Set
import argparse


def collectinfo(schema,arrays,structs):
    if schema in structs:
        return
    structs.add(schema)
    for field in schema.get_prop('fields'):
        if field.get_prop('type').get_prop('type') == 'array':
            arrays.append(field.get_prop('type').get_prop('items').get_prop('name'))
            collectinfo(field.get_prop('type').get_prop('items'), arrays, structs)
        elif field.get_prop('type').get_prop('type') == 'record':
            collectinfo(field.get_prop('type'), arrays, structs)
            pass
            
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate python avro module.')
    parser.add_argument('--namespace',default='namespace_name',help='c++ namespace')
    parser.add_argument('--module',default='module_name',help='python module name')
    parser.add_argument('--schema',help='input schema file',required='true')
    parser.add_argument('--output', type=argparse.FileType('w'),default='-',help='output file')
    args = parser.parse_args()

    templateLoader = jinja2.FileSystemLoader( searchpath="../" )
    templateEnv = jinja2.Environment( loader=templateLoader )
    
    TEMPLATE_FILE = "temp.jinja"
    template = templateEnv.get_template( TEMPLATE_FILE )
    
    schema = avro.schema.parse(open(args.schema,"rb").read())
    arrays=[]
    structs=Set([])
    collectinfo(schema, arrays, structs)
    templateVars={'module':args.module,'namespace':args.namespace,'arrays':arrays,'structs':structs}
    outputtext=template.render(templateVars)
    args.output.write(outputtext)


    