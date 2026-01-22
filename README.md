# DBoW - Database of Binary Words

> Implementation of **"Bags of Binary Words for Fast Place Recognition in Image Sequences"**  
> Paper by Dorian Gálvez-López and Juan D. Tardós (IEEE Transactions on Robotics, 2012)

---

## 📖 What Is This?

A C++ implementation for **visual place recognition** - detecting when a robot revisits a location using camera images.

**Paper's Achievement:**
- ✅ **22ms per frame** (26,300 images dataset)
- ✅ **100% precision** with high recall
- ✅ **10x faster** than SIFT/SURF approaches

---

## 🎯 Core Components

### **1. Binary Features (FAST + BRIEF)**
- **FAST:** Corner detection via Bresenham circle
- **BRIEF:** 256-bit binary descriptors
- Fast to compute, compact to store

### **2. Vocabulary Tree**
- Hierarchical k-medians clustering
- 1M words (k=10, depth=6)
- TF-IDF weighting

### **3. Image Database**
- **Inverse index:** Fast image retrieval
- **Direct index:** Quick feature matching
- Bag-of-words representation

### **4. Loop Detection**
- Temporal consistency checking
- Island grouping
- RANSAC geometric verification

---

## 🚀 Implementation Status

**Phase 1: Binary Features** (In Progress)
- ✅ Keypoint structure
- ✅ BRIEF descriptor type
- ✅ FAST corner detector
- ⏸️ BRIEF descriptor computation (Next)

**Phase 2: Vocabulary Tree** (Planned)
- ⏸️ Hamming distance
- ⏸️ K-medians clustering
- ⏸️ Tree builder

**Phase 3: Database** (Planned)
- ⏸️ Bag-of-words conversion
- ⏸️ Inverse index
- ⏸️ Direct index

**Phase 4: Loop Detection** (Planned)
- ⏸️ Similarity scoring
- ⏸️ Temporal consistency
- ⏸️ Geometric verification

**Phase 5: Android Integration** (Planned)
- ⏸️ JNI wrapper
- ⏸️ Camera input

---

## 📂 Project Structure

```
DBoW/
├── include/dbow/          # Public headers
│   ├── keypoint.h         # FAST keypoint structure
│   ├── descriptor.h       # BRIEF 256-bit descriptor
│   ├── feature.h          # Keypoint + descriptor
│   └── fast_detector.h    # FAST corner detection
├── src/dbow/              # Implementation
│   └── fast_detector.cpp  # FAST algorithm
└── docs/                  # Documentation
    ├── LEARNING_SUMMARY.md
    └── GITHUB_PUSH_GUIDE.md
```

---

## 🛠️ Build Instructions

```bash
# Clone repository
git clone https://github.com/AdithyaIniesta/DBoW.git
cd DBoW
git checkout develop  # Development branch

# Build (coming soon - CMake configuration pending)
mkdir build && cd build
cmake ..
make
```

---

## 📚 Paper Reference

**Citation:**
```bibtex
@article{galvez2012bags,
  title={Bags of binary words for fast place recognition in image sequences},
  author={Galvez-Lopez, Dorian and Tardos, Juan D},
  journal={IEEE Transactions on Robotics},
  volume={28},
  number={5},
  pages={1188--1197},
  year={2012},
  publisher={IEEE}
}
```

**Paper Link:** [IEEE Xplore](http://doriangalvez.com/papers/GalvezTRO12.pdf)

---

## 📖 Key Parameters (Table IV from Paper)

| Parameter | Value | Description |
|-----------|-------|-------------|
| FAST threshold | 10 | Corner response threshold |
| BRIEF length (L_b) | 256 bits | Descriptor size |
| BRIEF patch (S_b) | 48 pixels | Patch size around keypoint |
| Max features | 300 | Per image |
| Vocab branches (k_w) | 10 | Tree branching factor |
| Vocab depth (L_w) | 6 | Tree levels |
| Total words | 1,000,000 | 10^6 vocabulary size |
| Temporal consistency (k) | 3 | Required consecutive matches |
| Score threshold (α) | 0.3 | Normalized similarity |
| Direct index level (l) | 2 | For geometric verification |
| Min RANSAC inliers | 12 | Geometric check |

---

## 🎓 Learning Goals

This project serves as:
- ✅ Paper implementation from scratch
- ✅ Production-ready C++ for robotics
- ✅ Git workflow practice (branching, commits)
- ✅ Android app development preparation

---

## 📝 License

Educational implementation following the research paper.

---

## 🙏 Acknowledgments

Based on the excellent work by Dorian Gálvez-López and Juan D. Tardós.  
Paper: *Bags of Binary Words for Fast Place Recognition in Image Sequences* (IEEE TRO 2012)
