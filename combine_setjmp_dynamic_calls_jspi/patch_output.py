import os
import sys

def patch_output(output_file):
    with open(output_file, 'r+') as file:
        content = file.read()

        content = content.replace('assert(original.sig, `Missing __sig for ${x}`);', '')
        # content = content.replace('invoke_.*|', '')
        content = content.replace('let type = sigToWasmTypes(original.sig);', '''
            if(!original.sig && x.startsWith("invoke_")) {
                const l = "invoke_".length;
                original.sig = x[l] + "i" + x.slice(l + 1);
            }

            let type = sigToWasmTypes(original.sig);
        ''')

        file.seek(0)
        file.write(content)
        file.truncate()

# Usage example
output_file = sys.argv[1]
patch_output(output_file)
