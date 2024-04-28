# GatewayManagement

This section aims to remotely manage JSON configuration of LoRaWAN Gateways maintained by RFThings CO.,LTD & partners.

# FAQ ?

## How to update a configuration of a specific gateway?

1. Go to `./json_config/` folder & look for the corresponding JSON file that match your gateway EUI.
2. Modify & save the JSON config file.
3. Calculate MD5 Hash on the updated JSON config file.
4. Put the calculated MD5 Hash in the coresponding line in `index.txt` file.
5. Make a commit the remote reposistory.

Gateway will automatically clone the new configuration and apply. The process usally take 1-2 minutes since the time commit(s) pushed to remote reposistory.

## How to generate MD5?

Basically, any tools can be use to conduct this step.

However, do remind that there is a difference in newline symbol between different OS system. Before doing MD5 Hash calculation, make sure that all newline symbol(s) are converted to `\n`.

In this reposistory, we provide 2 ways to calculate MD5 HASH for all the JSON configuation file in the `./json_config/` folder.

### 1. generate_md5.sh

Located inside `./json_config/` folder, the `generate_md5.sh` script will run & print the MD5 hash in console for all files in the same folder.

### 2. md5_generate

Located inside `./md5_generate_src/` folder, the **md5_generate** program basically generate the `index.txt` file. There are source code & prebuilt binaries in the `./md5_generate_src/` folder. You can either use prebuilt binaries or compile your own program. Following steps demonstrate how to use:

1. Running the program from the `GatewayManagement` folder to archive the `index.tmp.txt` file.
2. Check the output `index.tmp.txt` file.
3. Rename `index.tmp.txt` to `index.txt`
4. Make a commit.

By default, the prebuilt binaries will manage following gateway:

- 7276ff000f061f15
- 7276ff000f062d6f
- 7276ff000f062d65
- 7276ff000f062cf3
- 7276ff000f062cf2

Adding new gateway(s) requires modify & re-compile the source code.

---