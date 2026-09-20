{
  description = "dwl - a dwm-like Wayland compositor";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "dwl";
        version = "0.8-dev";
        src = self;

        nativeBuildInputs = with pkgs; [
          pkg-config
          gnumake
          wayland-scanner
        ];

        buildInputs = with pkgs; [
          wayland
          wayland-protocols
          wlroots
          libinput
          libxkbcommon
          pixman
          libdrm
          mesa
          xwayland
          libxcb
          libxcb-wm
        ];

        buildPhase = "make";

        installPhase = ''
          runHook preInstall
          make install PREFIX=$out
          runHook postInstall
        '';

        meta = with pkgs.lib; {
          description = "dwm-like Wayland compositor";
          homepage = "https://github.com/djpohly/dwl";
          license = licenses.gpl3Only;
          platforms = platforms.linux;
          mainProgram = "dwl";
        };
      };

      devShells.${system}.default = pkgs.mkShell {
        buildInputs = (with pkgs; [
          gcc
          gnumake
          pkg-config
          wayland
          wayland-protocols
          wayland-scanner
          xwayland
          wlroots
          libinput
          libxkbcommon
          pixman
          libdrm
          mesa
          libxcb
          libxcb-wm
        ]);
      };
    };
}