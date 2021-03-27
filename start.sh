esp_version=v4.3-beta2

if [ ! -d esp-idf-${esp_version} ]; then
  if [ -f esp-idf-${esp_version}.zip ]; then
    rm esp-idf-${esp_version}.zip
  fi

  wget https://github.com/espressif/esp-idf/releases/download/${esp_version}/esp-idf-${esp_version}.zip

  unzip esp-idf-${esp_version}.zip
fi

./esp-idf-${esp_version}/install.sh

export IDF_PATH=esp-idf-${esp_version}
echo "export IDF_PATH=esp-idf-${esp_version}"

echo "source ${IDF_PATH}/export.sh"
