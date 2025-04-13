# Usage

Install [PlatformIO Core](https://platformio.org/install/cli)

Convert a gif using [image_to_c](https://github.com/bitbank2/image_to_c)

```bash
platformio run -t upload
```

Optionally generate `compile_commands.json` for clangd

```bash
platformio run -t compiledb
```

# Example Connection

Definitions in `include/config.h`

| ESP32 DOIT DEVKIT V1 | ST7789 |
| -------------------- | ------ |
| GND                  | GND    |
| 3V3                  | VCC    |
| GPIO18 (SCK)         | SCL    |
| GPIO23 (MOSI)        | SDA    |
| GPIO4                | RES    |
| GPIO2                | DC     |
| GPIO15               | CS     |
| -                    | BLK    |
