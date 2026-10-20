
const speed = document.getElementById("speed");
const targetSpeed = document.getElementById("targetSpeed");
const status = document.getElementById("status");

document.getElementById("apply").addEventListener("click", () => {
    const target = Number(targetSpeed.value);

    if (!Number.isFinite(target) || target < 0 || target > 120) {
        status.textContent = "Error: speed must be 0–120 km/h";
        return;
    }

    status.textContent = `Demo target speed set to ${target} km/h`;
});

document.getElementById("drive").addEventListener("click", () => {
    status.textContent = "Drive requested — simulation only";
});

document.getElementById("stop").addEventListener("click", () => {
    speed.textContent = "0";
    status.textContent = "Standby requested — simulation only";
});
