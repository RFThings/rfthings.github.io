# GatewayManagement

GatewayManagement is a toolset for remotely managing JSON configurations for LoRaWAN Gateways maintained by RFThings CO., LTD and our partners. This repository provides scripts and utilities to update gateway configurations, calculate MD5 hashes, and synchronize changes with gateways.

# FAQ

## Updating Gateway Configurations

### How do I update a configuration for a specific gateway?
1. Navigate to the `./json_config/` folder and locate the JSON file corresponding to your gateway's EUI.
2. Modify the JSON file, save your changes, and commit them to the repository.
3. Calculate the MD5 hash for the updated JSON file by running the `generate_md5.sh` script in the `./json_config/` folder.
4. Update the corresponding line in the `index.txt` file with the calculated MD5 hash.
5. Commit the changes to the `index.txt` file.
6. Push all commits to the remote repository.

The gateway will automatically fetch and apply the new configuration, typically within 1–2 minutes after the commits are pushed.

**Note**: MD5 hashes are sensitive to newline characters, which differ between operating systems (e.g., `\n` for Linux, `\r\n` for Windows). Ensure all JSON files use Linux-style newlines (`\n`). You can use tools like `Notepad++` or `vscode` to convert files if needed.

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