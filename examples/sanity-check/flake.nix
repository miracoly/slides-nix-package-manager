{
  description = "Nix sanity check";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      apps.default = {
        type = "app";
        program = toString (pkgs.writeShellScript "nix-check" ''
          echo "✅ Nix flakes are working on ${system}!"
        '');
      };

      devShells.default = pkgs.mkShell {
        packages = [pkgs.hello];
        shellHook = ''
          echo "🛠️  Welcome to the Nix dev shell (${system})"
          echo "Try running: hello"
        '';
      };
    });
}
