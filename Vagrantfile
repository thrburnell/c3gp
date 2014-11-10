# -*- mode: ruby -*-
# vi: set ft=ruby :

# Temporary change
# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  # Box used: "Official Ubuntu Server 14.04 LTS"
  config.vm.box = "ubuntu/trusty64"

  config.vm.network :private_network, ip: "192.168.111.222"


  config.vm.provider "virtualbox" do |v|
    v.memory = 2048
    v.cpus = 3
  end

  # Setting the provisioner
  config.vm.provision "ansible" do |ansible|
    ansible.playbook = "provision/playbook.yml"
    ansible.verbose = "v"
    ansible.vault_password_file = "~/.c3_vault_pass"
    ansible.extra_vars = {
      target: "all",
      user: "vagrant"
    }
  end

end
