#!/bin/bash

KEEB_PATH=$HOME/.keeb
QMK_PATH=$HOME/.qmk
KEYMAP_PATH=$QMK_PATH/keyboards/keyboardio/atreus/keymaps/hazelr2id

pushd $QMK_PATH
git pull
command cp -a $KEEB_PATH/keymap $KEYMAP_PATH
sudo qmk flash -kb keyboardio/atreus -km hazelr2id
command rm -rf $KEYMAP_PATH
popd
