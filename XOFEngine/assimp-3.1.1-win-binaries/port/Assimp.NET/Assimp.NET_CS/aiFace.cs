/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class aiFace : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal aiFace(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(aiFace obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~aiFace() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_aiFace(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public UintVector mIndices { get { return GetmIndices(); } }

  public uint mNumIndices {
    set {
      AssimpPINVOKE.aiFace_mNumIndices_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiFace_mNumIndices_get(swigCPtr);
      return ret;
    } 
  }

  public aiFace() : this(AssimpPINVOKE.new_aiFace__SWIG_0(), true) {
  }

  public aiFace(aiFace o) : this(AssimpPINVOKE.new_aiFace__SWIG_1(aiFace.getCPtr(o)), true) {
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public aiFace __set__(aiFace o) {
    aiFace ret = new aiFace(AssimpPINVOKE.aiFace___set__(swigCPtr, aiFace.getCPtr(o)), false);
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __equal__(aiFace o) {
    bool ret = AssimpPINVOKE.aiFace___equal__(swigCPtr, aiFace.getCPtr(o));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __nequal__(aiFace o) {
    bool ret = AssimpPINVOKE.aiFace___nequal__(swigCPtr, aiFace.getCPtr(o));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private UintVector GetmIndices() {
    IntPtr cPtr = AssimpPINVOKE.aiFace_GetmIndices(swigCPtr);
    UintVector ret = (cPtr == IntPtr.Zero) ? null : new UintVector(cPtr, true);
    return ret;
  }

}
