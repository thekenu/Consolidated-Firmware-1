if [ "$#" -ne 2 ]; then
    echo "Please provide the Series name and the .ELF file as arguments!"
    exit 1
else
    SERIES_NAME=$1
    ELF=$2
fi

# Example output of arm-none-eabi-size:
#
# $ arm-none-eabi-size /path/to/elf
#   text    data     bss     dec     hex filename
#  17652    1092    2784   21528    5418 /path/to/elf
size_output=($(arm-none-eabi-size $ELF | grep -P [0-9]+ -o))

text="${size_output[0]}"
data="${size_output[1]}"
bss="${size_output[2]}"

echo($text)
echo($data)
echo($bss)

curl \
  --header "Authorization: Token 92cb0c5d-2b14-41c0-9cfc-06fa089aa108" \
  --header "Content-Type: application/json" \
  --data "{\"values\":[{\"value\":\"$text\",\"line\":\"text\"},{\"value\":\"$data\",\"line\":\"data\"},{\"value\":\"$bss\",\"line\":\"bss\"}],\"sha\":\"${TRAVIS_COMMIT}\"}" \
  https://seriesci.com/api/thekenu/Consolidated-Firmware/$SERIES_NAME/many
