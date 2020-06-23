let
  pkgs = import <nixpkgs> {};
in
pkgs.mkShell {
  buildInputs = with pkgs; with xorg; [
    libX11 libXinerama libXft
  ];
}
