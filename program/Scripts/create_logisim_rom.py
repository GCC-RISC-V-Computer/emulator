#!/usr/bin/env python3


OFFSET = 0x4
PATH_MHC = "build/APP.mhc"
PATH_LOGISIM_ROM = "../debugger/programs/PINEAPPLE_program_logisim"

mhc_file = open(PATH_MHC)
instructions = mhc_file.read().split("\n")

logisim_output_data = ""

for instruction in instructions:
    instruction = instruction.strip('\'').replace('\\',"")

    # generate spaces between every two bytes:
    # from: "00080137"
    # to:   "00 08 01 37"
    logisim_output_data += " ".join([instruction[y] + instruction[y+1] for y in range(0, len(instruction), 2)]) + "\n"


OutputFile = open(PATH_LOGISIM_ROM, "w")

OutputFile.write("v2.0 raw\n")  
OutputFile.write(logisim_output_data.strip())

OutputFile.close()

print("Logisim ROM done.")










# #!/usr/bin/env python3

# OFFSET = 0x4
# PATH_MHC = "build/APP.mhc"

# mhc_file = open(PATH_MHC)
# txt = mhc_file.read()

# instructions = txt.split("\n")

# new_string = ""

# for item in instructions:
#     item = item.strip('\'')
#     item = item.replace('\\',"")
    
#     try:
#         item_4 = item[6:8]
#         item_3 = item[4:6]
#         item_2 = item[2:4]
#         item_1 = item[0:2]

#         new_string += item_1 + " " + item_2 + " " + item_3 + " " + item_4 + "\n" 
#     except:
#         pass

# start_adr = open("build/start_index.txt","r")
# adr = start_adr.readlines(0)
# start_adr.close()

# OutputFile = open("/Users/filipszkandera/Documents/Projekty/RISK/EEPROM_Program","w")
# OutputFile.write("v2.0 raw\n")  

# i = str(hex(int(str(adr)[2:-2])+OFFSET))[2:].zfill(3)
# x = i[:2] + " " + i[2:]

# # OutputFile.write("00 02 01 37 ff c1 01 13 " + x + "0 00 6F \n")
# OutputFile.write(new_string)
# OutputFile.close()

# OutputFile2 = open("/Users/filipszkandera/EEPROM_Program","w")
# OutputFile2.write("v2.0 raw\n")  

# i = str(hex(int(str(adr)[2:-2])+OFFSET))[2:].zfill(3)
# x = i[:2] + " " + i[2:]

# # OutputFile.write("00 02 01 37 ff c1 01 13 " + x + "0 00 6F \n")
# OutputFile2.write(new_string)
# OutputFile2.close()


# # print(new_string)
# print("Done.")


# #print("\n\n\n\n\n\n\n\n\n\n",x,"\n\n\n\n\n\n\n\n\n\n")