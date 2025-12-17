console.log("miniWLED UI loaded (15 FINAL)");

const API_STATE = "/json/state";
const API_EFFECTS = "/json/effects";
const POLL_INTERVAL = 1500;

// ===== UI LOCK =====
let uiLock = false;
let pollTimer = null;

function lockUi(delay = 250) {
  uiLock = true;
  setTimeout(() => (uiLock = false), delay);
}

// ===== PARAM LOCK (чтобы polling не дёргал ползунки во время drag) =====
const paramLock = { bri:false, sx:false, ix:false, color:false, fx:false };
const paramTimers = {};

function lockParam(name, delay = 600) {
  paramLock[name] = true;
  if (paramTimers[name]) clearTimeout(paramTimers[name]);
  paramTimers[name] = setTimeout(() => (paramLock[name] = false), delay);
}

// ===== DOM =====
const $ = (id) => document.getElementById(id);

// main controls
let powerToggle;

// color wheel
let colorPicker = null;

// sliders (Color tab)
let briSlider, speedSlider, intensitySlider;
let briVal, sxVal, ixVal;

// sliders (FX tab)
let briSliderFx, speedSliderFx, intensitySliderFx;
let briValFx, sxValFx, ixValFx;

// FX
let fxWheel, fxName;
let fxItems = [];
let effects = [];
let activeFx = 0;

// FX idle apply
let fxIdleTimer = null;
const FX_IDLE_APPLY_MS = 2000;

// programmatic scroll guard
let fxProgramScroll = false;

// ===== FALLBACK EFFECT NAMES (твои файлы) =====
const FX_FALLBACK = [
  "Ambient Warm",
  "Aurora",
  "Blackout",
  "Bouncing Balls",
  "Bouncing Colored Balls",
  "Center Glow",
  "Center Pulse",
  "Center Wave Warm",
  "Chase",
  "Chase Flash",
  "Chase Rainbow",
  "Cold Static",
  "Color Bounce",
  "Color Bounce Fade",
  "Color Loop VarDelay",
  "Color Twinkle",
  "Color Twinkle Dense",
  "Color Wave",
  "Cylon Bounce",
  "EMS All",
  "EMS One",
  "EMS Strobe",
  "Fire",
  "Fire Center",
  "Fire Dense",
  "Fire Slow",
  "Fire Soft",
  "Flicker",
  "Glitter Rainbow",
  "KITT",
  "Matrix",
  "New KITT",
  "Off Soft",
  "Pacman",
  "Plasma Center",
  "Plasma Soft",
  "Pop Horizontal",
  "Pulse Color",
  "Quad Bright Curve",
  "Radiation",
  "Rainbow Center Out",
  "Rainbow Cycle",
  "Rainbow Fade",
  "Rainbow Loop",
  "Rainbow Soft",
  "Rainbow Vertical",
  "Random Burst",
  "Random Color Pop",
  "Random March",
  "RGB Propeller",
  "Running Dots",
  "Running Lights",
  "RWB March",
  "Sin Bright Wave",
  "Sin Color Shift",
  "Slow Rainbow Breath",
  "Snow Sparkle",
  "Soft Breath",
  "Soft Color Noise",
  "Soft Fade Color",
  "Soft Gradient",
  "Sparkle",
  "Sparkle White",
  "Static Warm",
  "Strip March CCW",
  "Strip March CW",
  "Strobe",
  "Theater Chase Soft",
  "Twinkle Random",
  "Warm Breath",
  "Warm Center",
  "Warm Static",
  "White Glow",
  "White Temperature"
];

// ===== INIT =====
document.addEventListener("DOMContentLoaded", () => {
  // DOM
  powerToggle = $("powerToggle");

  // Color sliders
  briSlider = $("briSlider");
  speedSlider = $("speedSlider");
  intensitySlider = $("intensitySlider");
  briVal = $("briVal");
  sxVal = $("sxVal");
  ixVal = $("ixVal");

  // FX sliders
  briSliderFx = $("briSliderFx");
  speedSliderFx = $("speedSliderFx");
  intensitySliderFx = $("intensitySliderFx");
  briValFx = $("briValFx");
  sxValFx = $("sxValFx");
  ixValFx = $("ixValFx");

  // FX wheel
  fxWheel = $("fxWheel");
  fxName = $("fxName");

  bindNav();
  bindPower();
  initColorWheel();
  bindSliders();
  initFxWheel();

  fetchState();
  pollTimer = setInterval(fetchState, POLL_INTERVAL);
});

// ===== NAV =====
function bindNav(){
  const screens = document.querySelectorAll(".screen");
  const navButtons = document.querySelectorAll("[data-screen]");

  navButtons.forEach(btn => {
    btn.addEventListener("click", () => {
      const name = btn.dataset.screen;
      screens.forEach(s => s.classList.remove("active"));
      const target = document.getElementById(`screen-${name}`);
      if (target) target.classList.add("active");

      navButtons.forEach(b => b.classList.toggle("active", b.dataset.screen === name));
    });
  });
}

// ===== POWER =====
function bindPower(){
  if (!powerToggle) return;
  powerToggle.addEventListener("change", () => {
    lockUi(200);
    sendState({ on: powerToggle.checked });
  });
}

// ===== COLOR WHEEL =====
function initColorWheel(){
  const wheelEl = $("colorWheel");
  if (!wheelEl || !window.iro) return;

  colorPicker = new iro.ColorPicker("#colorWheel", {
    width: 260,
    wheelLightness: false,
    color: { r: 255, g: 255, b: 255 }
  });

  colorPicker.on("color:change", c => {
    lockParam("color", 700);
    lockUi(150);

    sendState({
      seg: [{
        col: [[
          Math.round(c.rgb.r),
          Math.round(c.rgb.g),
          Math.round(c.rgb.b)
        ]]
      }]
    });
  });
}

// ===== SLIDERS (две вкладки синхронно) =====
function bindSliders(){
  bindPairSlider("bri", briSlider, briVal, briSliderFx, briValFx);
  bindPairSlider("sx",  speedSlider, sxVal,  speedSliderFx, sxValFx);
  bindPairSlider("ix",  intensitySlider, ixVal, intensitySliderFx, ixValFx);
}

function bindPairSlider(key, s1, v1, s2, v2){
  const onInput = (val) => {
    lockParam(key, 700);
    lockUi(120);
    sendState({ [key]: val });
  };

  if (s1) {
    s1.addEventListener("input", () => {
      const val = Number(s1.value);
      if (v1) v1.textContent = String(val);
      // sync other
      if (s2 && Number(s2.value) !== val) s2.value = String(val);
      if (v2) v2.textContent = String(val);
      onInput(val);
    });
  }

  if (s2) {
    s2.addEventListener("input", () => {
      const val = Number(s2.value);
      if (v2) v2.textContent = String(val);
      // sync other
      if (s1 && Number(s1.value) !== val) s1.value = String(val);
      if (v1) v1.textContent = String(val);
      onInput(val);
    });
  }
}

// ===== FX WHEEL =====
function initFxWheel(){
  if (!fxWheel) return;

  // 1) сразу строим fallback (без ожиданий)
  effects = FX_FALLBACK.slice();
  renderFxList();

  // 2) если прошивка отдаёт реальные имена/порядок — заменяем
  fetch(API_EFFECTS)
    .then(r => (r.ok ? r.json() : null))
    .then(list => {
      if (!Array.isArray(list) || list.length === 0) return;
      effects = list.map(x => String(x ?? ""));
      renderFxList();
      // после подмены — аккуратно центрируем текущий activeFx
      centerFx(activeFx, false);
      updateFxName(activeFx);
      setActiveFxClass(activeFx);
    })
    .catch(()=>{ /* тихо */ });

  // UX: scroll -> preview, apply after 2s idle
  fxWheel.addEventListener("scroll", () => {
    if (fxProgramScroll) return;

    const idx = getCenteredFxIndex();
    if (idx == null) return;

    // Live preview only (без отправки)
    setActiveFxClass(idx);
    updateFxName(idx);

    // Debounce apply
    if (fxIdleTimer) clearTimeout(fxIdleTimer);
    fxIdleTimer = setTimeout(() => {
      // если за время ожидания центр поменялся — применим новый
      const finalIdx = getCenteredFxIndex();
      if (finalIdx == null) return;

      // применяем только если реально другой
      if (finalIdx !== activeFx) {
        applyFx(finalIdx);
      } else {
        // даже если тот же — просто фиксируем класс
        setActiveFxClass(activeFx);
        updateFxName(activeFx);
      }
    }, FX_IDLE_APPLY_MS);
  }, { passive:true });

  // Tap on item -> apply immediately
  fxWheel.addEventListener("click", (e) => {
    const item = e.target.closest(".fx-item");
    if (!item) return;
    const idx = Number(item.dataset.fx);
    if (!Number.isFinite(idx)) return;

    // моментально применяем
    applyFx(idx);
  });

  // PC wheel support (делаем только вертикально и без “скачков”)
  fxWheel.addEventListener("wheel", (e) => {
    // чтобы колесо мыши не скроллило весь экран
    e.preventDefault();
    fxWheel.scrollTop += e.deltaY;
  }, { passive:false });
}

function renderFxList(){
  fxWheel.innerHTML = "";
  fxItems = [];

  effects.forEach((name, idx) => {
    const d = document.createElement("div");
    d.className = "fx-item";
    d.dataset.fx = String(idx);
    d.textContent = name || `FX ${idx}`;
    fxWheel.appendChild(d);
    fxItems.push(d);
  });

  // стартовые состояния
  setActiveFxClass(activeFx);
  updateFxName(activeFx);

  // важный момент: центрируем текущий fx один раз
  centerFx(activeFx, false);
}

function applyFx(idx){
  idx = clamp(idx, 0, effects.length - 1);

  lockParam("fx", 900);
  lockUi(140);

  activeFx = idx;

  setActiveFxClass(activeFx);
  updateFxName(activeFx);

  // мягко центрируем выбранное
  centerFx(activeFx, true);

  // отправка
  sendState({ fx: activeFx });
}

function centerFx(idx, smooth){
  const el = fxWheel.querySelector(`.fx-item[data-fx="${idx}"]`);
  if (!el) return;

  fxProgramScroll = true;
  el.scrollIntoView({ block: "center", behavior: smooth ? "smooth" : "auto" });

  // снимаем флаг после анимации
  setTimeout(() => { fxProgramScroll = false; }, smooth ? 350 : 50);
}

function setActiveFxClass(idx){
  if (!fxItems.length) return;
  fxItems.forEach((it, i) => it.classList.toggle("active", i === idx));
}

function updateFxName(idx){
  if (!fxName) return;
  fxName.textContent = effects[idx] ?? `FX ${idx}`;
}

function getCenteredFxIndex(){
  if (!fxItems.length) return null;

  const rect = fxWheel.getBoundingClientRect();
  const centerY = rect.top + rect.height / 2;

  let bestIdx = 0;
  let bestDist = 1e9;

  for (let i = 0; i < fxItems.length; i++){
    const r = fxItems[i].getBoundingClientRect();
    const mid = r.top + r.height / 2;
    const dist = Math.abs(mid - centerY);
    if (dist < bestDist) {
      bestDist = dist;
      bestIdx = i;
    }
  }
  return bestIdx;
}

function clamp(v,a,b){ return Math.max(a, Math.min(b, v)); }

// ===== POLLING =====
function fetchState(){
  if (uiLock) return;

  fetch(API_STATE)
    .then(r => (r.ok ? r.json() : null))
    .then(state => {
      if (!state) return;
      applyState(state);
    })
    .catch(()=>{});
}

function applyState(state){
  // Power
  if (powerToggle && typeof state.on === "boolean") {
    powerToggle.checked = state.on;
  }

  // bri/sx/ix -> оба набора ползунков
  applySliderFromState("bri", state.bri, briSlider, briVal, briSliderFx, briValFx);
  applySliderFromState("sx",  state.sx,  speedSlider, sxVal, speedSliderFx, sxValFx);
  applySliderFromState("ix",  state.ix,  intensitySlider, ixVal, intensitySliderFx, ixValFx);

  // Color
  if (!paramLock.color && state.seg && state.seg[0] && state.seg[0].col) {
    const c = state.seg[0].col[0];
    if (c && colorPicker) {
      colorPicker.color.rgb = { r: c[0], g: c[1], b: c[2] };
    }
  }

  // FX (если пришёл с устройства)
  if (!paramLock.fx && typeof state.fx === "number") {
    const fx = clamp(state.fx, 0, effects.length - 1);
    if (fx !== activeFx) {
      activeFx = fx;
      setActiveFxClass(activeFx);
      updateFxName(activeFx);
      centerFx(activeFx, false);
    }
  }
}

function applySliderFromState(key, value, s1, v1, s2, v2){
  if (paramLock[key]) return;
  if (typeof value !== "number") return;

  const val = clamp(value, 0, 255);

  if (s1 && Number(s1.value) !== val) s1.value = String(val);
  if (v1) v1.textContent = String(val);

  if (s2 && Number(s2.value) !== val) s2.value = String(val);
  if (v2) v2.textContent = String(val);
}

// ===== SEND =====
function sendState(payload){
  fetch(API_STATE, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload)
  }).catch(()=>{});
}