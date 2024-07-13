     do k=1,nlev
        dp(:,:,k) = ( hvcoord%hyai(k+1) - hvcoord%hyai(k) )*hvcoord%ps0 + &
             ( hvcoord%hybi(k+1) - hvcoord%hybi(k) )*elem(ie)%state%ps_v(:,:,np1)
     enddo





     do q=1,qsize
        do k=1,nlev
           elem(ie)%state%Q(:,:,k,q) = elem(ie)%state%Qdp(:,:,k,q,np1_qdp)/dp(:,:,k)
        enddo
     enddo
     
     
     
        do k=1,nlev
           elem(ie)%state%vtheta_dp(:,:,k,nt)=elem(ie)%state%vtheta_dp(:,:,k,nt)-&
                theta_ref(:,:,k,ie)
           elem(ie)%state%phinh_i(:,:,k,nt)=elem(ie)%state%phinh_i(:,:,k,nt)-&
                phi_ref(:,:,k,ie)
           elem(ie)%state%dp3d(:,:,k,nt)=elem(ie)%state%dp3d(:,:,k,nt)-&
                dp_ref(:,:,k,ie)
        enddo     



  do n=n0,n1
    ! set prognostic state variables at level midpoints
    elem%state%v   (:,:,1,:,n)        = u
    elem%state%v   (:,:,2,:,n)        = v
    elem%state%dp3d(:,:,:,  n)        = dp
    elem%state%ps_v(:,:,    n)        = ps
    elem%state%phis(:,:)              = phis
    elem%state%vtheta_dp(:,:,:,n)   = (Rstar/Rgas)*T*dp*((p/p0)**(-kappa))

    elem%state%w_i (:,:,:,  n)   = w_i
    elem%state%phinh_i(:,:,:, n) = g*zi
  end do


     do i=1,np
     do j=1,np
       do k=1,nlev
        if (k.eq.1) then
          norminfJ0(i,j) = max(norminfJ0(i,j),(abs(JacD(k,i,j))+abs(JacU(k,i,j))))
        elseif (k.eq.nlev) then
          norminfJ0(i,j) = max(norminfJ0(i,j),(abs(JacL(k,i,j))+abs(JacD(k,i,j))))
        else
          norminfJ0(i,j) = max(norminfJ0(i,j),(abs(JacL(k,i,j))+abs(JacD(k,i,j))+ &
            abs(JacU(k,i,j))))
        end if
      end do
    end do
    end do


        do k=1,nlev
           ! average interface quantity to midpoints:
           temp(:,:,k) = (( eta_dot_dpdn(:,:,k)+eta_dot_dpdn(:,:,k+1))/2)*&
                (elem(ie)%state%w_i(:,:,k+1,n0)-elem(ie)%state%w_i(:,:,k,n0))
           
           ! theta vadv term at midoints
           theta_vadv(:,:,k)= eta_dot_dpdn(:,:,k+1)*vtheta_i(:,:,k+1) - &
                eta_dot_dpdn(:,:,k)*vtheta_i(:,:,k)
        enddo


          do k=1,nlev
              vtens(:,:,1,k,ie)=dt*vtens(:,:,1,k,ie)*elem(ie)%rspheremp(:,:)  ! u
              vtens(:,:,2,k,ie)=dt*vtens(:,:,2,k,ie)*elem(ie)%rspheremp(:,:)  ! v
              stens(:,:,k,1,ie)=dt*stens(:,:,k,1,ie)*elem(ie)%rspheremp(:,:)  ! dp3d
              stens(:,:,k,2,ie)=dt*stens(:,:,k,2,ie)*elem(ie)%rspheremp(:,:)  ! theta
              stens(:,:,k,3,ie)=dt*stens(:,:,k,3,ie)*elem(ie)%rspheremp(:,:)  ! w
              stens(:,:,k,4,ie)=dt*stens(:,:,k,4,ie)*elem(ie)%rspheremp(:,:)  ! phi

              !add ref state back
              elem(ie)%state%vtheta_dp(:,:,k,nt)=elem(ie)%state%vtheta_dp(:,:,k,nt)+&
                   theta_ref(:,:,k,ie)
              elem(ie)%state%phinh_i(:,:,k,nt)=elem(ie)%state%phinh_i(:,:,k,nt)+&
                   phi_ref(:,:,k,ie)
              elem(ie)%state%dp3d(:,:,k,nt)=elem(ie)%state%dp3d(:,:,k,nt)+&
                   dp_ref(:,:,k,ie)

           enddo



  do ie=nets,nete
     
     kptr=0
     call edgeVunpack_nlyr(edge_g,elem(ie)%desc,vtens(:,:,:,:,ie),2*nlev,kptr,6*nlev)
     kptr=2*nlev
     call edgeVunpack_nlyr(edge_g,elem(ie)%desc,stens(:,:,:,:,ie),4*nlev,kptr,6*nlev)
     
     ! apply inverse mass matrix, accumulate tendencies
     do k=1,nlev
        elem(ie)%state%v(:,:,1,k,nt)=elem(ie)%state%v(:,:,1,k,nt) + &
             mu*dt*vtens(:,:,1,k,ie)*elem(ie)%rspheremp(:,:)

        elem(ie)%state%v(:,:,2,k,nt)=elem(ie)%state%v(:,:,2,k,nt) + &
             mu*dt*vtens(:,:,2,k,ie)*elem(ie)%rspheremp(:,:)
        
        elem(ie)%state%dp3d(:,:,k,nt)=elem(ie)%state%dp3d(:,:,k,nt) &
             +mu_s*dt*stens(:,:,k,1,ie)*elem(ie)%rspheremp(:,:)
        
        elem(ie)%state%vtheta_dp(:,:,k,nt)=elem(ie)%state%vtheta_dp(:,:,k,nt) &
             +mu_s*dt*stens(:,:,k,2,ie)*elem(ie)%rspheremp(:,:)

        elem(ie)%state%w_i(:,:,k,nt)=elem(ie)%state%w_i(:,:,k,nt) &
             +mu_s*dt*stens(:,:,k,3,ie)*elem(ie)%rspheremp(:,:)
        
        elem(ie)%state%phinh_i(:,:,k,nt)=elem(ie)%state%phinh_i(:,:,k,nt) &
             +mu_s*dt*stens(:,:,k,4,ie)*elem(ie)%rspheremp(:,:)
        
     enddo
  enddo
  
  
  

  ! convert vtheta_dp -> theta
  do ie=nets,nete            
     do k=1,nlev
        elem(ie)%state%vtheta_dp(:,:,k,nt)=&
             elem(ie)%state%vtheta_dp(:,:,k,nt)*elem(ie)%state%dp3d(:,:,k,nt)
     enddo

     ! finally update w at the surface: 
     elem(ie)%state%w_i(:,:,nlevp,nt) = (elem(ie)%state%v(:,:,1,nlev,nt)*elem(ie)%derived%gradphis(:,:,1) + &
          elem(ie)%state%v(:,:,2,nlev,nt)*elem(ie)%derived%gradphis(:,:,2))/g
  enddo
  
    




     do q=1,qsize
        do k=1,nlev
           do j=1,np
              do i=1,np
                 v1 = dt*elem(ie)%derived%FQ(i,j,k,q)
                 !if (elem(ie)%state%Qdp(i,j,k,q,np1) + v1 < 0 .and. v1<0) then
                 if (elem(ie)%state%Qdp(i,j,k,q,np1_qdp) + v1 < 0 .and. v1<0) then
                    !if (elem(ie)%state%Qdp(i,j,k,q,np1) < 0 ) then
                    if (elem(ie)%state%Qdp(i,j,k,q,np1_qdp) < 0 ) then
                       v1=0  ! Q already negative, dont make it more so
                    else
                       !v1 = -elem(ie)%state%Qdp(i,j,k,q,np1)
                       v1 = -elem(ie)%state%Qdp(i,j,k,q,np1_qdp)
                    endif
                 endif
                 !elem(ie)%state%Qdp(i,j,k,q,np1) = elem(ie)%state%Qdp(i,j,k,q,np1)+v1
                 elem(ie)%state%Qdp(i,j,k,q,np1_qdp) = elem(ie)%state%Qdp(i,j,k,q,np1_qdp)+v1
                 if (q==1) then
                    elem(ie)%derived%FQps(i,j)=elem(ie)%derived%FQps(i,j)+v1/dt
                 endif
              enddo
           enddo
        enddo
     enddo
     
     
     
     
     
