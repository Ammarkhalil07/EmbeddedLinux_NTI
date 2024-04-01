# Mounting RootFS Through NFS

This guide outlines the steps to mount the root filesystem through NFS.

### Step 1: Install NFS server:
```bash
sudo apt-get install nfs-kernel-server
```

---

### Step 2: Configure exports file (/etc/exports):
- Edit the `/etc/exports` file to specify the shared directory and access permissions.
- Add the following line:

```bash
/home/ammar/rootfs 192.168.1.100(rw,no_root_squash,no_subtree_check)
```
- `/home/ammar/rootfs`: Specifies the directory to be shared via NFS.
- `192.168.1.100`: Specifies the IP address of the NFS client with access permissions.
- `(rw,no_root_squash,no_subtree_check)`: Specifies the access permissions for the client.
- `rw`: Grants read/write access to the client.
- `no_root_squash`: Allows the root user on the client to access files as the root user on the server.
- `no_subtree_check`: Disables subtree checking for performance reasons.

---

### Step 3: Refresh exports:

Updates the NFS server's export table:

```bash
sudo exportfs -r
```

---

### Step 4: Configure U-Boot bootargs:

- Edit the U-Boot environment to specify boot arguments (`bootargs`) for the kernel.
- Set the following bootargs:
```bash
setenv bootargs console=ttyAMA0 root=/dev/nfs ip=192.168.1.100::::eth0 nfsroot=192.168.1.102:/home/ammar/rootfs,nfsvers=3,tcp rw init=/bin/sh
```
`bootargs` Explanation:

- **`bootargs=`**: Indicates that the following string is the boot arguments for the kernel.
- **`console=ttyAMA0`**: Sets the serial console for kernel messages to `ttyAMA0`.
- **`root=/dev/nfs`**: Specifies the root filesystem as an NFS mount.
- **`ip=1192.168.1.100::::eth0`**: Sets the IP address and network interface for network communication.
- **`nfsroot=192.168.1.102:/home/ammar/rootfs`**: Specifies the NFS server and directory to be used as the root filesystem.
- **`nfsvers=3`**: Specifies that NFS version 3 should be used for the NFS mount.
- **`tcp`**: Specifies that TCP should be used as the transport protocol for NFS communication.
- **`rw`**: Specifies that the root filesystem should be mounted with read/write permissions.
- **`init=/bin/sh`**: Specifies the initial process (`init`) that the kernel should execute after the root filesystem is mounted.

