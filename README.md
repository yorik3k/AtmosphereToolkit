# Atmosphere Toolkit

## What is it

**Atmosphere Toolkit** is a plugin for speeding up work in the Unreal Engine editor. It was written to accelerate work with lighting settings and scene optimization.

The plugin is a tool that I originally wrote for myself, but I thought it would be appropriate to share it with people. It does not claim to be universal or unique. It grew out of the need to optimize my own workflow as a UE5 developer.

The plugin does not do the impossible — it can only help you speed up the monotonous work on a level.

---

## Main Features

The plugin is divided into **modules**. This allows it to be scaled to suit your goals.

### Atmosphere Adjustment Module

The module is designed to speed up work with the main actors responsible for **Lumen** on a level:

- **Directional Light**
- **Sky Light**
- **Exponential Height Fog**
- and others.

The module allows you to use **presets** stored in a **DataTable**, as well as configure parameters **manually**.

**Main feature:** parameters are grouped in a **single window**, which slightly speeds up the initial setup of lighting on a level or its reconfiguration.

**Presets** allow you to save settings and reuse them, not only on a single level. In addition to the presets already available, you can also save and use your own presets. They are generated based on the current settings and entered into the corresponding fields.

### Optimization Module

This module works with **optimization**. Its main focus is to speed up optimization work — for example, by applying **Draw Distance** or **HISM** to selected objects on a large scale.

---

## Installation

1. Copy the plugin into your project's `Plugins/` folder.
2. Rebuild the project.
3. Find the plugin in **Window → Atmosphere Toolkit** or **Scene Optimizer**.

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

**Note:** Unreal Engine is a trademark of Epic Games, Inc. Use of this plugin requires a valid Unreal Engine license.

## Compatibility

- **Unreal Engine 5.7.x**

---
