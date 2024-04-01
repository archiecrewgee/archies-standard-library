#! /bin/bash
set -eo pipefail

python -m menuconfig kconfig && python -m genconfig kconfig